/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "fcurve.h"

#include <databaseplugin/classes/rootobject.h>

#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

static bool lessThan(const FPoint &a, const FPoint &b)
{
    return a.x() < b.x();
}

namespace AudioCarver {
namespace Internal {

class FCurvePrivate
{
public:
    QList<FPoint> points;

    FCurvePrivate()
    {
    }

    ~FCurvePrivate()
    {
    }
};

} // namespace Internal
} // namespace AudioCarver

FCurve::FCurve(QObject *parent)
    :   Database::Object(parent)
    ,   d(new FCurvePrivate)
{
    Q_CHECK_PTR(d);
}

FCurve::~FCurve()
{
    delete d;  d = 0;
}

const QList<FPoint> &FCurve::points() const
{
    return d->points;
}

int FCurve::pointCount() const
{
    return d->points.count();
}

const FPoint &FCurve::pointAt(int i) const
{
    return d->points.at(i);
}

void FCurve::setPointAt(const FPoint &point, int i)
{
    d->points[i] = point;
    qSort(d->points.begin(), d->points.end(), lessThan);
}

int FCurve::indexOfPoint(const FPoint &point)
{
    return d->points.indexOf(point);
}

void FCurve::appendPoint(const FPoint &point)
{
    d->points.append(point);
    qSort(d->points.begin(), d->points.end(), lessThan);
}

void FCurve::removePoint(const FPoint &point)
{
    d->points.removeOne(point);
    qSort(d->points.begin(), d->points.end(), lessThan);
}

void FCurve::removePoint(int i)
{
    d->points.removeAt(i);
    qSort(d->points.begin(), d->points.end(), lessThan);
}

bool FCurve::read(QXmlStreamReader &in)
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
            FPoint point;

            foreach (const QXmlStreamAttribute &att, atts) {
                const QString name = att.name().toString();
                const QString value = att.value().toString();
                if (name == "x")
                    point.setX(QVariant(value).toDouble());
                else if (name == "y")
                    point.setY(QVariant(value).toDouble());
                else if (name == "curve")
                    point.setCurvePoint(value == "1");
            }

            d->points.append(point);
        }
    }

    return true;
}

void FCurve::write(QXmlStreamWriter &out) const
{
    Database::RootObject *root = this->root();
    Q_ASSERT(root);

    out.writeStartElement(className());

    // Write properties.
    out.writeAttribute("id", objectName());

    // Write points.
    for (int i = 0;  i < d->points.count();  ++i) {
        out.writeStartElement("point");
        out.writeAttribute("x", root->variantToString(QVariant(d->points.at(i).x())));
        out.writeAttribute("y", root->variantToString(QVariant(d->points.at(i).y())));
        out.writeAttribute("curve", root->variantToString(QVariant(d->points.at(i).isCurvePoint())));
        out.writeEndElement();
    }

    out.writeEndElement();
}
