/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_csound_synthesizer.h"
#include <ac_core_namespace.h>
#include <ac_core_point.h>
#include <mi_core_math.h>
#include <mi_core_utilities.h>
#include <idatabase.h>
#include <imodelitem.h>
#include <csound.h>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QtDebug>

using namespace Ac;
using namespace Mi;

static void writeTableFile(const QString &fileName, const PointList &points, int valueCount)
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

    // Calculate table values.
    QVector<qreal> table_values(valueCount);
    const qreal div_x = 1.0 / qreal(valueCount - 1);
    const int n_points = points.count();
    int i = 0; // current values index
    int j = 1; // current point index
    while (i < valueCount && j < n_points) {
        qreal cur_x = 0;
        const QPointF point_offset = normalized_points[j - 1];
        if (BezierCurve != points.at(j).curveType
                || j == 0
                || j == n_points - 1) {
            // Calculate line using 2 points.
            const QPointF to_point = normalized_points[j] - point_offset;
            const qreal to_x = roundToNearest(to_point.x(), div_x);
            const qreal to_y = to_point.y();
            const int n_values = (to_x / div_x) + 0.5;
            for (int k = 0;  k < n_values;  ++k) {
                // TODO:  Figure out why i is incrementing past the valueCount
                //          when to_x is small.
                i = qMin(i, valueCount - 1);
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
                while (i_bezier < bezier_pts.count()
                       && bezier_pts[i_bezier].x() < cur_x)
                    ++i_bezier;
                ++i;
            }
            ++j;
        }
        ++j;
    }
    while (i < valueCount) {
        table_values[i] = normalized_points.last().y();
        ++i;
    }

    // Write table values.
    for (int i = 0;  i < valueCount;  ++i) {
        if (0 < i)
            table_file.write("\n");
        table_file.write(qPrintable(QString("%1").arg(table_values[i], 0, 'f', 6)));
    }

    table_file.close();
}

namespace Csound {

void Synthesizer::renderTrack(int trackNumber)
{
    IModelItem *track = IDatabase::instance()->rootItem()->findItem(TrackListItem)->itemAt(trackNumber);
    if (!track)
        return;
    IDatabase *database = IDatabase::instance();
    const QString db_file_name = database->fileName();
    if (db_file_name.isEmpty())
        return;
    const QString root_dir_name = QFileInfo(db_file_name).path();
    QDir root_dir(root_dir_name);
    IModelItem *project_settings = database->rootItem()->findItem(ProjectSettingsItem);
    const int curve_rate = get<int>(project_settings, CurveRateRole);
    QString output_dir_name = get<QString>(project_settings, OutputDirectoryRole);
    if (output_dir_name.isEmpty())
        output_dir_name = db_file_name + "-output";
    if (!root_dir.mkpath(output_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << output_dir_name;
        return;
    }
    const QString csound_dir_name = output_dir_name + "/csound";
    if (!root_dir.mkpath(csound_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << csound_dir_name;
        return;
    }
    const QString track_name = get<QString>(track, NameRole).toLower();
    const QString sco_file_name = csound_dir_name + "/" + track_name + ".sco";
    const QString table_dir_name = csound_dir_name + "/" + track_name;
    if (!root_dir.mkpath(table_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << table_dir_name;
        return;
    }
    QString instrument_dir_name = get<QString>(project_settings, InstrumentDirectoryRole);
    if (instrument_dir_name.isEmpty())
        instrument_dir_name = applicationTreeDirectory() + "instruments";
    else if (QDir::isRelativePath(instrument_dir_name))
        instrument_dir_name = root_dir_name + "/" + instrument_dir_name;
    QString instrument_file_name = instrument_dir_name + "/" + get<QString>(track, InstrumentRole);
    if (!instrument_file_name.endsWith(".orc"))
        instrument_file_name += ".orc";
    const IModelItem *notes = track->findItem(NoteListItem);
    const int n = notes->itemCount();

    // Write table and .sco files.
    QFile sco_file(sco_file_name);
    if (!sco_file.open(QIODevice::Text | QIODevice::WriteOnly)) {
        qDebug() << Q_FUNC_INFO << ": Error opening sco file" << sco_file_name;
        return;
    }
    sco_file.write("\n");
    for (int i = 0;  i < n;  ++i) {
        const int id = i + 1001;
        const QString curve_file_name = table_dir_name + QString("/note.%1.txt").arg(id);
        IModelItem *note_item = notes->itemAt(i);
        IModelItem *curve_item = note_item->findItem(PitchCurveItem);
        PointList points = get<PointList>(curve_item, PointsRole);
        qreal start_time = points.first().pos.x();
        qreal duration = points.last().pos.x() - start_time;
        qreal pitch = points.first().pos.y();
        qreal volume = get<qreal>(note_item, VolumeRole);
        const int table_value_count = toPowerOfTwo((duration + 0.5) * curve_rate);
        if (table_value_count <= 2) {
            qDebug() << Q_FUNC_INFO << ": Table count is less than 2";
            continue;
        }
        writeTableFile(curve_file_name, points, table_value_count);
        const QString table_sco_create_line = QString("f %1 %2 %3 %4 \"%5\"\n")
                .arg(id)
                .arg(start_time, 0, 'f', 6)
                .arg(table_value_count)
                .arg(-23)
                .arg(curve_file_name);
        const QString table_sco_destroy_line = QString("f%1 %2\n")
                .arg(-id)
                .arg(start_time + duration + 1.0, 0, 'f', 6);
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

    // Render track.
    csoundInitialize(0, 0, 0);
    CSOUND *csound = csoundCreate(0);
    if (!csound)
        qDebug() << Q_FUNC_INFO << ": Error creating csound";
    const QString opcode_dir = applicationTreeDirectory();
    const QByteArray opcode_dir_ba = opcode_dir.toLocal8Bit();
    csoundSetGlobalEnv("OPCODEDIR64", opcode_dir_ba.constData());
    const QString include_dir = applicationTreeDirectory() + "instruments";
    const QByteArray include_dir_ba = include_dir.toLocal8Bit();
    csoundSetGlobalEnv("INCDIR", include_dir_ba.constData());
    if (CSOUND_SUCCESS != csoundPreCompile(csound)) {
        qDebug() << Q_FUNC_INFO << ": Error precompiling csound";
        return;
    }
    char first_arg[] = "";
    const QString audio_dir_name = output_dir_name + "/audio";
    if (!root_dir.mkpath(audio_dir_name)) {
        qDebug() << Q_FUNC_INFO << ": Error making path" << audio_dir_name;
        return;
    }
    QString audio_file_type = get<QString>(project_settings, AudioFileTypeRole);
    if (audio_file_type.isEmpty()) {
#           ifdef Q_OS_MAC
        {   audio_file_type = "aiff";
        }
#           else
        {   audio_file_type = "wav";
        }
#           endif
    }
    const QString audio_file_name = audio_dir_name + "/" + track_name + "." + audio_file_type;
    const QString output_flag = "-o" + audio_file_name;
    QByteArray output_flag_ba = output_flag.toLocal8Bit();
    char *output_arg = output_flag_ba.data();
    char displays_arg[] = "-d";
    char bit_depth_arg[] = "-f";
    const QString sample_rate_flag = QString("-r%1").arg(get<int>(project_settings, SampleRateRole));
    QByteArray sample_rate_flag_ba = sample_rate_flag.toLocal8Bit();
    char *sample_rate_arg = sample_rate_flag_ba.data();
    const QString control_rate_flag = QString("-k%1").arg(get<int>(project_settings, ControlRateRole));
    QByteArray control_rate_flag_ba = control_rate_flag.toLocal8Bit();
    char *control_rate_arg = control_rate_flag_ba.data();
    QByteArray orc_file_ba = instrument_file_name.toLocal8Bit();
    char *orc_arg = orc_file_ba.data();
    QByteArray sco_file_ba = sco_file_name.toLocal8Bit();
    char *sco_arg = sco_file_ba.data();
    const int argc = 8;
    char *argv[argc] = {
        first_arg,
        output_arg,
        displays_arg,
        bit_depth_arg,
        sample_rate_arg,
        control_rate_arg,
        orc_arg, sco_arg
    };
    for (int i = 1;  i < argc;  ++i)
        qDebug() << Q_FUNC_INFO << "arg" << i << "==" << argv[i];
    if (CSOUND_SUCCESS != csoundCompile(csound, argc, argv)) {
        qDebug() << Q_FUNC_INFO << ": Error compiling csound";
        return;
    }
    csoundPerform(csound);
    csoundDestroy(csound);
}

}
