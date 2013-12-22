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

#include "spmboks.h"

SpmBoks::SpmBoks( int x, int y, Animasjon *n, Animasjon *b, Sprite *i ) : Sprite( x, y )
{
	ny = n;
	brukt = b;
	innhold = i;
	innhold->setSynlig( false );
	truffet = false;

	setAnimasjon( ny );
}

SpmBoks::~ SpmBoks()
{
	delete ny;
	delete brukt;
}

void SpmBoks::treff()
{
	setAnimasjon( brukt );
	innhold->setSynlig( true );
	truffet = true;
}

bool SpmBoks::isTruffet() const
{
	return truffet;
}

Sprite* SpmBoks::getInnhold() const
{
	return innhold;
}
