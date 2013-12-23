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

#ifndef SPRITE_H
#define SPRITE_H

#include "animasjon.h"

class Sprite
{
    public:
        Sprite( int x, int y );
        virtual ~Sprite();
        QPoint getPosisjon() const;
        void setPosisjon( QPoint p );
        Animasjon* getAnimasjon() const;
        void setAnimasjon( Animasjon* a );
        void oppdaterAni( int tid );
        bool getSynlig() const;
        void setSynlig( bool s );
        QRect getRect() const;
        int getX() const;
        void setX( int x );
        int getY() const;
        void setY( int y );
        int getHoyde() const;
        int getLengde() const;
        bool getFjernes() const;
        void setFjernes( bool f );

    private:
        QPoint posisjon;
        Animasjon* ani;
        bool synlig, fjernes;
};

#endif
