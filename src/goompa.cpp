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

#include "goompa.h"

Goompa::Goompa( int x, int y, double xh, double yh, Animasjon* h, Animasjon* d ) : FarligVesen( x, y )
{
	hoppe = h;
	dod = d;
	setXHast( xh );
	setYHast( yh );
	setAnimasjon( hoppe );
}

Goompa::~Goompa()
{
	delete hoppe;
	delete dod;
}

void Goompa::oppdaterPos( int tid )
{
	if ( getLever() )
		setAnimasjon( hoppe );
	else
		setAnimasjon( dod );

	Sprite::oppdaterAni( tid );
}

void Goompa::kolliderY()
{
	if ( getLever() )
		setYHast( -1.2 );
}

void Goompa::kolliderX()
{
	setXHast( getXHast() * -1 );
}
