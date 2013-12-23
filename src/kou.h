/***************************************************************************
 *   Copyright (C) 2006 by Christian Ihle                                  *
 *   kontakt@usikkert.net                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef KOU_H
#define KOU_H

#include "vesen.h"
#include "status.h"
#include "ildkule.h"

class Kou : public Vesen
{
    public:
        Kou( int x, int y, Animasjon* aVGaa, Animasjon* aVStaa, Animasjon* aVHeie, Animasjon* aVDod, Animasjon* aHGaa, Animasjon* aHStaa, Animasjon* aHHeie, Animasjon* aHDod, Animasjon* aLitenVGaa, Animasjon* aLitenVStaa, Animasjon* aLitenVHeie, Animasjon* aLitenVDod, Animasjon* aLitenHGaa, Animasjon* aLitenHStaa, Animasjon* aLitenHHeie, Animasjon* aLitenHDod, Animasjon* aVGaaGal, Animasjon* aVStaaGal, Animasjon* aVHeieGal, Animasjon* aVDodGal, Animasjon* aHGaaGal, Animasjon* aHStaaGal, Animasjon* aHHeieGal, Animasjon* aHDodGal, Animasjon* i );
        ~Kou();
        void oppdaterPos( int tid );
        void hopp( bool ekstrahopp = false );
        void kolliderY();
        void setSeier( bool s );
        bool getSeier() const;
        void setStatus( Status* s );
        Ildkule* getIldkule() const;

    private:
        Animasjon *aVenstreGaa, *aVenstreStaa, *aVenstreHeie, *aVenstreDod, *aHoyreGaa, *aHoyreStaa, *aHoyreHeie, *aHoyreDod, *aLitenVenstreGaa, *aLitenVenstreStaa, *aLitenVenstreHeie, *aLitenVenstreDod, *aLitenHoyreGaa, *aLitenHoyreStaa, *aLitenHoyreHeie, *aLitenHoyreDod, *aVenstreGaaGal, *aVenstreStaaGal, *aVenstreHeieGal, *aVenstreDodGal, *aHoyreGaaGal, *aHoyreStaaGal, *aHoyreHeieGal, *aHoyreDodGal, *ildkule;
        bool bakken, seier;
        Status* status;
};

#endif
