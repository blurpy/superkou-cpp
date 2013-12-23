
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

#ifndef ANIMASJON_H
#define ANIMASJON_H

#include <QtGui>

struct Frame
{
    QPixmap bilde;
    int sluttTid;

    Frame( QPixmap b, int s )
    {
        bilde = b;
        sluttTid = s;
    }
};

class Animasjon
{
    public:
        Animasjon();
        ~Animasjon();
        void leggTilBilde( QPixmap bilde, int varighet );
        const QPixmap &hentBilde() const;
        void oppdater( int tid );

    private:
        QList<Frame> frames;
        int totalVarighet, bruktTid;
        int aktivFrameNr;
};

#endif
