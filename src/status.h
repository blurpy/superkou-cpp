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

#ifndef STATUS_H
#define STATUS_H

#include <QtGui>

class Status
{
    public:
        Status();
        ~Status();
        enum Tilstand { INTRO, SPILL, PAUSE, DOD, HELTDOD, LASTBRETT, FERDIGBRETT, FERDIGSPILL };
        enum Storrelse { LITEN, VANLIG, GAL };
        int finnBruktTid();
        void oppdaterTid();
        int getBrettNr() const;
        void setBrettNr( int b );
        void incBrettNr();
        void setLiv( int l );
        int getLiv() const;
        void setOst( int o );
        int getOst() const;
        void incOst();
        void incLiv();
        void decLiv();
        void setSpungy( int s );
        int getSpungy() const;
        void incSpungy();
        const Tilstand &getTilstand() const;
        void setTilstand( Tilstand t );
        const QPixmap &getMiniOst() const;
        const QPixmap &getMiniSpungy() const;
        const QPixmap &getMiniKou() const;
        int getFPS() const;
        int getSpillTid() const;
        void setSpillTid( int t );
        const Storrelse &getStorrelse() const;
        void setStorrelse( Storrelse s );
        bool isSkadd() const;
        void setSkadd( bool s );
        bool isIldkuleKlar();

    private:
        int liv, ost, spungy, brettnr, fps, spilltid, msteller, fpsteller, ildkuleteller;
        Tilstand tilstand;
        Storrelse storrelse;
        double nytid, forrigetid;
        QPixmap miniost, minikou, minispungy;
        bool skadd;

};

#endif
