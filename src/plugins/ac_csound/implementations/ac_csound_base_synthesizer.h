/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CSOUND_BASE_SYNTHESIZER_H
#define AC_CSOUND_BASE_SYNTHESIZER_H

#include <isynthesizer.h>

class IAggregate;

namespace Base {

class Synthesizer : public ISynthesizer
{
    IAggregate *_aggregate;

public:
    void *queryInterface(int interfaceType) const;

protected:
    Synthesizer();

    void initialize()
    {}

    void reset()
    {}
};

}

#endif
