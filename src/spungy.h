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

#ifndef SPUNGY_H
#define SPUNGY_H

#include "farligvesen.h"

class Spungy : public FarligVesen
{
    public:
        Spungy( int x, int y, double xh, double yh, Animasjon* aVGaa, Animasjon* aVDod, Animasjon* aHGaa, Animasjon* aHDod );
        ~Spungy();
        void oppdaterPos( int tid );
        void kolliderX();

    private:
        Animasjon *aVenstreGaa, *aVenstreDod, *aHoyreGaa, *aHoyreDod;
};

#endif
