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

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <csound.h>

class CsoundSynthesizerPrivate
{
public:
    void renderTrack(const IModelItem *track)
    {
        if (!track)
            return;

        const QString instrument = track->data(Ac::InstrumentRole).toString();

        const IModelItem *notes = track->findModelItemList(Ac::NoteItem);
        const int n = notes->modelItemCount();
        for (int i = 0;  i < n;  ++i) {
        }
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
