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

#ifndef KART_H
#define KART_H

#include "kou.h"
#include "spungy.h"
#include "banan.h"
#include "ost.h"
#include "spmboks.h"
#include "oppgradering.h"
#include "goompa.h"

class Kart
{
	public:
		Kart( QString url );
		~Kart();
		QPixmap* hentBilde( int x, int y ) const;
		int hentHoyde() const;
		int hentBredde( int x ) const;
		int hentKartHoyde() const;
		int hentKartBredde( int x ) const;
		Kou* getKou() const;
		const QList<Sprite*> &getSprites() const;
		const QPixmap &getBakgrunn() const;
		int getTid() const;
		void settInnSprite( Sprite* s );
		void slettSprite( Sprite* s );

	private:
		QList< QList<QPixmap*> > bildekart;
		QMap<char, QPixmap*> bildeoversikt;
		Kou* kou;
		QList<Sprite*> sprites;
		QPixmap bakgrunn;
		int tid;
		QPixmap* finnUrl( char tegn, int x, int y );
		void lagBanan( int x, int y );
		void lagKou( int x, int y );
		void lagSpungy( int x, int y );
		void lagOst( int x, int y );
		void lagOppgradering( int x, int y );
		void lagGoompa( int x, int y );
		void lagBoksOst( int x, int y );
};

#endif
