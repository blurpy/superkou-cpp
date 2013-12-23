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

#include "sprite.h"

Sprite::Sprite( int x, int y )
{
    posisjon.setX( x );
    posisjon.setY( y );
    ani = 0;
    synlig = true;
    fjernes = false;
}

Sprite::~Sprite()
{

}

QPoint Sprite::getPosisjon() const
{
    return posisjon;
}

void Sprite::setPosisjon( QPoint p )
{
    posisjon = p;
}

Animasjon* Sprite::getAnimasjon() const
{
    return ani;
}

void Sprite::setAnimasjon( Animasjon* a )
{
    ani = a;
}

void Sprite::oppdaterAni( int tid )
{
    ani->oppdater( tid );
}

bool Sprite::getSynlig() const
{
    return synlig;
}

void Sprite::setSynlig( bool s )
{
    synlig = s;
}

QRect Sprite::getRect() const
{
    return QRect( posisjon, ani->hentBilde().size() );
}

int Sprite::getX() const
{
    return posisjon.x();
}

void Sprite::setX( int x )
{
    posisjon.setX( x );
}

int Sprite::getY() const
{
    return posisjon.y();
}

void Sprite::setY( int y )
{
    posisjon.setY( y );
}

int Sprite::getHoyde() const
{
    return ani->hentBilde().height();
}

int Sprite::getLengde() const
{
    return ani->hentBilde().width();
}

bool Sprite::getFjernes() const
{
    return fjernes;
}

void Sprite::setFjernes( bool f )
{
    fjernes = f;
}
