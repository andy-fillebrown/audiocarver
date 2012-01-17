/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include <ac_csoundsynthesizer.h>

#include <ac_namespace.h>
#include <ac_point.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <csound.h>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

static bool isPowerOfTwo(int n)
{
    const int size = 8 * sizeof(int);
    for (int i = 1;  i < size;  i++)
        if (n == (1 << i))
            return true;
    return false;
}

static int toPowerOfTwo(int n, int min = 4)
{
    if (n < min)
        n = min;
    if (isPowerOfTwo(n))
        return n;
    const int size = 8 * sizeof(int);
    int i = 0;
    for (;  i < size;  i++) {
        if (n == 0) {
            n = 1 << i;
            return n;
        }
        n = n >> 1;
        if (isPowerOfTwo(n)) {
            n = n << (i + 2);
            return n;
        }
    }
    return min;
}

static qreal intersectionY(const qreal &x1, // start x
                           const qreal &x2, // end x
                           const qreal &y1, // start y
                           const qreal &y2, // end y
                           const qreal &intersectionX)
{
    qreal intY = 0.0;
    if (y1 == y2)
        intY = y1;
    else {
        const qreal x2_x1 = x2 - x1;
        const qreal intX_x1 = intersectionX - x1;
        if ((x2_x1 == 0.0) || (intX_x1 == 0.0))
            intY = y1;
        else
            intY = y1 + (((y2 - y1) / x2_x1) * intX_x1);
    }
    return intY;
}

static QPointF bezierPoint(const QPointF &pt1, // start point
                           const QPointF &pt2, // control point
                           const QPointF &pt3, // end point
                           const qreal t)
{
    const qreal mu2 = t * t;
    const qreal mum1 = 1 - t;
    const qreal mum12 = mum1 * mum1;
    return QPointF(pt1.x() * mum12 + 2 * pt2.x() * mum1 * t + pt3.x() * mu2,
                   pt1.y() * mum12 + 2 * pt2.y() * mum1 * t + pt3.y() * mu2);
}

inline qreal round(const qreal from, const qreal to)
{
    const qreal r = fmod(from, to);
    const qreal td2 = to / qreal(2);
    if (r == 0)
        return from;
    else if (r < td2)
        return from - r;
    else
        return from + (to - r);
}

static void writeTableFile(const QString &fileName, const PointList &points, int controlRate)
{
    QFile table_file(fileName);
    if (!table_file.open(QIODevice::WriteOnly)) {
        qDebug() << Q_FUNC_INFO << ": Error opening table file for write" << fileName;
        return;
    }

    const QPointF &start_point = points.first().pos;
    const qreal start_x = start_point.x();
    const qreal scale_x = 1.0 / (points.last().pos.x() - start_x);
    const qreal start_y = start_point.y();
    QList<QPointF> normalized_points;
    foreach (const Point &point, points)
        normalized_points.append(QPointF(scale_x * (point.pos.x() - start_x), point.pos.y() - start_y));

    const qreal duration = points.last().pos.x() - points.first().pos.x();
    const int table_count = toPowerOfTwo((duration + 0.5) * controlRate);
    if (table_count <= 2) {
        qDebug() << Q_FUNC_INFO << ": Table count is less than 2";
        return;
    }

    // Calculate table values.
    QVector<qreal> table_values(table_count);
    const qreal div_x = 1.0 / qreal(table_count - 1);
    const int n_points = points.count();
    int i = 0; // current values index
    int j = 1; // current point index
    while (i < table_count && j < n_points) {
        qreal cur_x = 0;
        const QPointF point_offset = normalized_points[j - 1];
        if (Ac::BezierCurve != points.at(j).curveType
                || j == 0
                || j == n_points - 1) {
            // Calculate line using 2 points.
            const QPointF to_point = normalized_points[j] - point_offset;
            const qreal to_x = round(to_point.x(), div_x);
            const qreal to_y = to_point.y();
            const int n_values = (to_x / div_x) + 0.5;
            for (int k = 0;  k < n_values;  ++k) {
                table_values[i] = intersectionY(0, to_x, 0, to_y, cur_x);
                table_values[i] += point_offset.y();
                cur_x += div_x;
                ++i;
            }
        } else {
            // Calculate bezier curve using 3 points.
            const QPointF from_pt;
            const QPointF ctrl_pt = normalized_points[j] - point_offset;
            const QPointF to_pt = normalized_points[j + 1] - point_offset;
            const qreal to_x = to_pt.x();
            if (qFuzzyCompare(to_x, 0))
                continue;
            QList<QPointF> bezier_pts;
            const qreal norm_div_x = div_x / to_x;
            const int n_values = (to_x / div_x) + 0.5;
            for (int k = 0;  k < n_values;  k++) {
                bezier_pts.append(bezierPoint(from_pt, ctrl_pt, to_pt, cur_x));
                cur_x += norm_div_x;
            }
            bezier_pts.append(to_pt);
            cur_x = 0;
            int i_bezier = 1;
            for (int k = 0;  k < n_values;  k++) {
                table_values[i] = intersectionY(bezier_pts[i_bezier - 1].x(), bezier_pts[i_bezier].x(),
                                                bezier_pts[i_bezier - 1].y(), bezier_pts[i_bezier].y(),
                                                cur_x);
                table_values[i] += point_offset.y();
                cur_x += div_x;
                while (i_bezier < bezier_pts.count() && bezier_pts[i_bezier].x() < cur_x)
                    ++i_bezier;
                ++i;
            }
            ++j;
        }
        ++j;
    }
    while (i < table_count) {
        table_values[i] = normalized_points.last().y();
        ++i;
    }

    // Write table values.
    for (int i = 0;  i < table_count;  ++i) {
        if (0 < i)
            table_file.write("\n");
        table_file.write(qPrintable(QString("%1").arg(table_values[i], 0, 'f', 6)));
    }

    table_file.close();
}

class CsoundSynthesizerPrivate
{
public:
    void renderTrack(const IModelItem *track)
    {
        if (!track)
            return;

        const QString db_file_name = IDatabase::instance()->fileName();
        if (db_file_name.isEmpty())
            return;

        const QString root_dir_name = QFileInfo(db_file_name).path();
        QDir root_dir(root_dir_name);

        const IModel *model = IModel::instance();
        const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));

        const int control_rate = project_settings->data(Ac::ControlRateRole).toInt();

        QString output_dir_name = project_settings->data(Ac::OutputDirectoryRole).toString();
        if (output_dir_name.isEmpty())
            output_dir_name = root_dir_name + "/output";
        if (!root_dir.mkpath(output_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << output_dir_name;
            return;
        }

        const QString csound_dir_name = output_dir_name + "/csound";
        if (!root_dir.mkpath(csound_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << csound_dir_name;
            return;
        }

        const QString track_name = track->data(Mi::NameRole).toString().toLower();
        const QString sco_file_name = csound_dir_name + "/" + track_name + ".sco";

        const QString table_dir_name = csound_dir_name + "/" + track_name;
        if (!root_dir.mkpath(table_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << table_dir_name;
            return;
        }

        const QString audio_dir_name = output_dir_name + "/audio";
        if (!root_dir.mkpath(audio_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << audio_dir_name;
            return;
        }

        QString audio_file_type = project_settings->data(Ac::AudioFileTypeRole).toString();
        if (audio_file_type.isEmpty())
            audio_file_type = "wav";
        const QString audio_file_name = audio_dir_name + "/" + track_name + "." + audio_file_type;

        QString instrument_dir_name = project_settings->data(Ac::InstrumentDirectoryRole).toString();
        if (instrument_dir_name.isEmpty())
            instrument_dir_name = QCoreApplication::applicationDirPath() + "/../instruments";

        QString instrument_file_name = instrument_dir_name + "/" + track->data(Ac::InstrumentRole).toString();
        if (!instrument_file_name.endsWith(".orc"))
            instrument_file_name += ".orc";

        const IModelItem *notes = track->findModelItemList(Ac::NoteItem);
        const int n = notes->modelItemCount();

        // Write table and .sco files.
        QFile sco_file(sco_file_name);
        if (!sco_file.open(QIODevice::Text | QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening sco file" << sco_file_name;
            return;
        }
        for (int i = 0;  i < n;  ++i) {
            const int id = i + 1;

            const QString curve_file_name = table_dir_name + QString("/note.%1.txt").arg(id);
            IModelItem *note_item = notes->modelItemAt(i);
            IModelItem *curve_item = note_item->findModelItem(Ac::PitchCurveItem);
            PointList points = curve_item->data(Ac::PointsRole).value<PointList>();

            writeTableFile(curve_file_name, points, control_rate);

            qreal start_time = points.first().pos.x();
            qreal duration = points.last().pos.x() - start_time;
            qreal pitch = points.first().pos.y();
            qreal volume = note_item->data(Ac::VolumeRole).toReal();

            const QString table_sco_create_line = QString("f %1 %2\n")
                    .arg(id)
                    .arg(start_time, 0, 'f', 6);

            const QString table_sco_destroy_line = QString("f%1 %2\n")
                    .arg(-id)
                    .arg(start_time + duration, 0, 'f', 6);

            const QString note_sco_line = QString("i 2 %2 %3 %4 %5 %6 %7\n")
                    .arg(start_time, 0, 'f', 6)
                    .arg(duration, 0, 'f', 6)
                    .arg(pitch, 0, 'f', 6)
                    .arg(volume, 0, 'f', 6)
                    .arg(id)
                    .arg(0);

            sco_file.write(qPrintable(table_sco_create_line));
            sco_file.write(qPrintable(note_sco_line));
            sco_file.write(qPrintable(table_sco_destroy_line));
            sco_file.write("\n");
        }
        sco_file.write("e\n");
        sco_file.close();
    }
};

CsoundSynthesizer::CsoundSynthesizer()
    :   d(new CsoundSynthesizerPrivate)
{}

CsoundSynthesizer::~CsoundSynthesizer()
{
    delete d;
}

void CsoundSynthesizer::renderTrack(int trackNumber)
{
    const IModel *model = IModel::instance();
    const IModelItem *track = model->itemFromIndex(model->index(trackNumber, model->listIndex(Ac::TrackItem)));
    d->renderTrack(track);
}
