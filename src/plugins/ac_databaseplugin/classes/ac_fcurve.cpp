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

#include "ac_fcurve.h"

#include <ac_fpoint.h>

#include <mi_root.h>

#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace Private;

static bool lessThan(const AcFPoint &a, const AcFPoint &b)
{
    return a.x() < b.x();
}

namespace Private {

class AcFCurveData : public MiLinkableObjectData
{
public:
    QList<AcFPoint> points;

    AcFCurveData(AcFCurve *q)
        :   MiLinkableObjectData(q)
    {}

    void sortPoints()
    {
        qSort(points.begin(), points.end(), lessThan);
    }
};

} // namespace Private

AcFCurve::AcFCurve(QObject *parent)
    :   MiObject(parent)
    ,   d(new AcFCurveData(this))
{}

AcFCurve::~AcFCurve()
{
    delete d;
}

const QList<AcFPoint> &AcFCurve::points() const
{
    return d->points;
}

int AcFCurve::pointCount() const
{
    return d->points.count();
}

const AcFPoint &AcFCurve::pointAt(int i) const
{
    return d->points.at(i);
}

void AcFCurve::setPointAt(const AcFPoint &point, int i)
{
    d->points[i] = point;
    d->sortPoints();
    emit pointsChanged();
}

int AcFCurve::indexOfPoint(const AcFPoint &point)
{
    return d->points.indexOf(point);
}

void AcFCurve::appendPoint(const AcFPoint &point)
{
    d->points.append(point);
    d->sortPoints();
    emit pointsChanged();
}

void AcFCurve::removePoint(const AcFPoint &point)
{
    d->points.removeOne(point);
    d->sortPoints();
    emit pointsChanged();
}

void AcFCurve::removePoint(int i)
{
    d->points.removeAt(i);
    d->sortPoints();
    emit pointsChanged();
}

bool AcFCurve::read(QXmlStreamReader &in)
{
    Q_ASSERT(in.name() == className());

    // Read properties.
    QXmlStreamAttributes atts = in.attributes();
    foreach (const QXmlStreamAttribute &att, atts) {
        QString name = att.name().toString();
        if (name == "id")
            setObjectName(att.value().toString());
    }

    // Read points.
    d->points.clear();
    while (!in.atEnd()) {
        QXmlStreamReader::TokenType tokenType = in.readNext();
        if (tokenType == QXmlStreamReader::Characters)
            continue;
        const QString currentClassName = in.name().toString();
        if (tokenType == QXmlStreamReader::EndElement && currentClassName == className())
            break;
        if (tokenType == QXmlStreamReader::StartElement) {
            Q_ASSERT(in.name() == "point");
            atts = in.attributes();
            AcFPoint point;
            foreach (const QXmlStreamAttribute &att, atts) {
                const QString name = att.name().toString();
                const QString value = att.value().toString();
                if (name == "x")
                    point.setX(QVariant(value).toDouble());
                else if (name == "y")
                    point.setY(QVariant(value).toDouble());
                else if (name == "curve")
                    point.setCurved(value == "1");
            }
            d->points.append(point);
        }
    }
    d->sortPoints();

    return true;
}

void AcFCurve::write(QXmlStreamWriter &out) const
{
    MiRoot *root = this->root();
    Q_ASSERT(root);

    out.writeStartElement(className());

    // Write properties.
    out.writeAttribute("id", objectName());

    // Write points.
    for (int i = 0;  i < d->points.count();  ++i) {
        out.writeStartElement("point");
        out.writeAttribute("x", root->variantToString(QVariant(d->points.at(i).x())));
        out.writeAttribute("y", root->variantToString(QVariant(d->points.at(i).y())));
        out.writeAttribute("curve", root->variantToString(QVariant(d->points.at(i).isCurved())));
        out.writeEndElement();
    }

    out.writeEndElement();
}
