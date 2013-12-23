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

#include "status.h"

Status::Status()
{
	minikou.load( QString( "bilder/kou_mini.png" ) );
	minispungy.load( QString( "bilder/spungy_mini.png" ) );
	miniost.load( QString( "bilder/ost3_mini.png" ) );

	liv = 0;
	ost = 0;
	spungy = 0;
	brettnr = 1;
	fps = 0;
	spilltid = 0;
	msteller = 0;
	fpsteller = 0;
	ildkuleteller = 0;
	tilstand = INTRO;
	storrelse = LITEN;
	skadd = false;

	oppdaterTid();
}

Status::~ Status()
{

}

// Brukes blant annet til å regne ut fps, gjenværende tid, og animasjoner.
// Returnerer antall millisekunder siden forrige gang den ble kjørt.
int Status::finnBruktTid()
{
	QTime qt = QTime::currentTime();
	nytid = time( 0 ) + qt.msec() / 1000.0;
	int tid = (int) ( ( nytid - forrigetid ) * 1000 );
	forrigetid = nytid;

	msteller += tid;
	fpsteller++;

	if ( msteller > 1000 )
	{
		msteller = msteller % 1000;
		fps = fpsteller;
		fpsteller = 0;

		if ( spilltid > 0 )
			spilltid--;
	}

	if ( ildkuleteller < 700 )
		ildkuleteller += fps;

	return tid;
}

// Resetter tidstellerne.
void Status::oppdaterTid()
{
	QTime qt = QTime::currentTime();
	nytid = time( 0 ) + qt.msec() / 1000.0;
	forrigetid = nytid;
}

void Status::setLiv( int l )
{
	liv = l;
}

int Status::getLiv() const
{
	return liv;
}

void Status::setOst( int o )
{
	ost = o;
}

int Status::getOst() const
{
	return ost;
}

void Status::incOst()
{
	ost++;
}

void Status::incLiv()
{
	liv++;
}

void Status::decLiv()
{
	liv--;
}

const Status::Tilstand &Status::getTilstand() const
{
	return tilstand;
}

void Status::setTilstand( Tilstand t )
{
	tilstand = t;
}

const QPixmap &Status::getMiniOst() const
{
	return miniost;
}

const QPixmap &Status::getMiniSpungy() const
{
	return minispungy;
}

const QPixmap &Status::getMiniKou() const
{
	return minikou;
}

int Status::getBrettNr() const
{
	return brettnr;
}

void Status::setBrettNr( int b )
{
	brettnr = b;
}

void Status::incBrettNr()
{
	brettnr++;
}

void Status::setSpungy( int s )
{
	spungy = s;
}

int Status::getSpungy() const
{
	return spungy;
}

void Status::incSpungy()
{
	spungy++;
}

int Status::getSpillTid() const
{
	return spilltid;
}

int Status::getFPS() const
{
	return fps;
}

void Status::setSpillTid( int t )
{
	spilltid = t;
}

const Status::Storrelse &Status::getStorrelse() const
{
	return storrelse;
}

void Status::setStorrelse( Status::Storrelse s )
{
	storrelse = s;
}

bool Status::isSkadd() const
{
	return skadd;
}

void Status::setSkadd( bool s )
{
	skadd = s;
}

bool Status::isIldkuleKlar()
{
	if ( ildkuleteller >= 700 )
	{
		ildkuleteller = 0;
		return true;
	}

	else
		return false;
}
