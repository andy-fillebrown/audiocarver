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

#ifndef AC_CSOUNDSYNTHESIZER_H
#define AC_CSOUNDSYNTHESIZER_H

#include <ac_isynthesizer.h>

class CsoundSynthesizerPrivate;

class CsoundSynthesizer : public ISynthesizer
{
    Q_OBJECT

public:
    CsoundSynthesizer();
    ~CsoundSynthesizer();

    void renderTrack(int trackNumber);

private:
    CsoundSynthesizerPrivate *d;
};

#endif // AC_CSOUNDSYNTHESIZER_H
