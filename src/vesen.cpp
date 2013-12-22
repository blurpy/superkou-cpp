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

#include "vesen.h"

Vesen::Vesen( int x, int y ) : Sprite( x, y )
{
	lever = true;
	xhast = 0;
	yhast = 0;
}

Vesen::~ Vesen()
{

}

void Vesen::setLever( bool l )
{
	lever = l;
}

bool Vesen::getLever() const
{
	return lever;
}

double Vesen::getXHast() const
{
	return xhast;
}

void Vesen::setXHast( double xh )
{
	xhast = xh;
}

double Vesen::getYHast() const
{
	return yhast;
}

void Vesen::setYHast( double yh )
{
	yhast = yh;
}

void Vesen::oppdaterPos( int tid )
{
	setX( (int) ( getX() + xhast * tid ) );
	setY( (int) ( getY() + yhast * tid ) );
	Sprite::oppdaterAni( tid );
}

void Vesen::kolliderX()
{

}

void Vesen::kolliderY()
{

}
