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

#include "kou.h"

Kou::Kou( int x, int y, Animasjon* aVGaa, Animasjon* aVStaa, Animasjon* aVHeie, Animasjon* aVDod, Animasjon* aHGaa, Animasjon* aHStaa, Animasjon* aHHeie, Animasjon* aHDod, Animasjon* aLitenVGaa, Animasjon* aLitenVStaa, Animasjon* aLitenVHeie, Animasjon* aLitenVDod, Animasjon* aLitenHGaa, Animasjon* aLitenHStaa, Animasjon* aLitenHHeie, Animasjon* aLitenHDod, Animasjon* aVGaaGal, Animasjon* aVStaaGal, Animasjon* aVHeieGal, Animasjon* aVDodGal, Animasjon* aHGaaGal, Animasjon* aHStaaGal, Animasjon* aHHeieGal, Animasjon* aHDodGal, Animasjon* i ) : Vesen( x, y )
{
    aVenstreGaa = aVGaa;
    aVenstreStaa = aVStaa;
    aVenstreHeie = aVHeie;
    aVenstreDod = aVDod;
    aHoyreGaa = aHGaa;
    aHoyreStaa = aHStaa;
    aHoyreHeie = aHHeie;
    aHoyreDod = aHDod;

    aLitenVenstreGaa = aLitenVGaa;
    aLitenVenstreStaa = aLitenVStaa;
    aLitenVenstreHeie = aLitenVHeie;
    aLitenVenstreDod = aLitenVDod;
    aLitenHoyreGaa = aLitenHGaa;
    aLitenHoyreStaa = aLitenHStaa;
    aLitenHoyreHeie = aLitenHHeie;
    aLitenHoyreDod = aLitenHDod;

    aVenstreGaaGal = aVGaaGal;
    aVenstreStaaGal = aVStaaGal;
    aVenstreHeieGal = aVHeieGal;
    aVenstreDodGal = aVDodGal;
    aHoyreGaaGal = aHGaaGal;
    aHoyreStaaGal = aHStaaGal;
    aHoyreHeieGal = aHHeieGal;
    aHoyreDodGal = aHDodGal;

    ildkule = i;

    setAnimasjon( aLitenHoyreStaa );

    bakken = false;
    seier = false;
}

Kou::~ Kou()
{
    delete aVenstreGaa;
    delete aVenstreStaa;
    delete aVenstreHeie;
    delete aVenstreDod;
    delete aHoyreGaa;
    delete aHoyreStaa;
    delete aHoyreHeie;
    delete aHoyreDod;

    delete aLitenVenstreGaa;
    delete aLitenVenstreStaa;
    delete aLitenVenstreHeie;
    delete aLitenVenstreDod;
    delete aLitenHoyreGaa;
    delete aLitenHoyreStaa;
    delete aLitenHoyreHeie;
    delete aLitenHoyreDod;

    delete aVenstreGaaGal;
    delete aVenstreStaaGal;
    delete aVenstreHeieGal;
    delete aVenstreDodGal;
    delete aHoyreGaaGal;
    delete aHoyreStaaGal;
    delete aHoyreHeieGal;
    delete aHoyreDodGal;

    delete ildkule;
}

void Kou::oppdaterPos( int tid )
{
    if ( status->getStorrelse() == Status::LITEN )
    {
        if ( getXHast() > 0 )
            setAnimasjon( aLitenHoyreGaa );
        else if ( getXHast() < 0 )
            setAnimasjon( aLitenVenstreGaa );
        else
        {
            if ( getAnimasjon() == aLitenHoyreGaa || getAnimasjon() == aHoyreStaa )
                setAnimasjon( aLitenHoyreStaa );
            else if ( getAnimasjon() == aLitenVenstreGaa || getAnimasjon() == aVenstreStaa )
                setAnimasjon( aLitenVenstreStaa );

            if ( getLever() == false )
            {
                if ( getAnimasjon() == aLitenHoyreStaa )
                    setAnimasjon( aLitenHoyreDod );
                else if ( getAnimasjon() == aLitenVenstreStaa )
                    setAnimasjon( aLitenVenstreDod );
            }

            if ( seier == true )
            {
                if ( getAnimasjon() == aLitenHoyreStaa )
                    setAnimasjon( aLitenHoyreHeie );
                else if ( getAnimasjon() == aLitenVenstreStaa )
                    setAnimasjon( aLitenVenstreHeie );
            }
        }
    }

    else if ( status->getStorrelse() == Status::VANLIG )
    {
        if ( getXHast() > 0 )
            setAnimasjon( aHoyreGaa );
        else if ( getXHast() < 0 )
            setAnimasjon( aVenstreGaa );
        else
        {
            if ( getAnimasjon() == aHoyreGaa || getAnimasjon() == aHoyreStaaGal ||getAnimasjon() == aLitenHoyreStaa )
                setAnimasjon( aHoyreStaa );
            else if ( getAnimasjon() == aVenstreGaa || getAnimasjon() == aVenstreStaaGal || getAnimasjon() == aLitenVenstreStaa )
                setAnimasjon( aVenstreStaa );

            if ( getLever() == false )
            {
                if ( getAnimasjon() == aHoyreStaa )
                    setAnimasjon( aHoyreDod );
                else if ( getAnimasjon() == aVenstreStaa )
                    setAnimasjon( aVenstreDod );
            }

            if ( seier == true )
            {
                if ( getAnimasjon() == aHoyreStaa )
                    setAnimasjon( aHoyreHeie );
                else if ( getAnimasjon() == aVenstreStaa )
                    setAnimasjon( aVenstreHeie );
            }
        }
    }

    else if ( status->getStorrelse() == Status::GAL )
    {
        if ( getXHast() > 0 )
            setAnimasjon( aHoyreGaaGal );
        else if ( getXHast() < 0 )
            setAnimasjon( aVenstreGaaGal );
        else
        {
            if ( getAnimasjon() == aHoyreGaaGal || getAnimasjon() == aHoyreStaa || getAnimasjon() == aLitenHoyreStaa )
                setAnimasjon( aHoyreStaaGal );
            else if ( getAnimasjon() == aVenstreGaaGal || getAnimasjon() == aVenstreStaa || getAnimasjon() == aLitenVenstreStaa )
                setAnimasjon( aVenstreStaaGal );

            if ( getLever() == false )
            {
                if ( getAnimasjon() == aHoyreStaaGal )
                    setAnimasjon( aHoyreDodGal );
                else if ( getAnimasjon() == aVenstreStaaGal )
                    setAnimasjon( aVenstreDodGal );
            }

            if ( seier == true )
            {
                if ( getAnimasjon() == aHoyreStaaGal )
                    setAnimasjon( aHoyreHeieGal );
                else if ( getAnimasjon() == aVenstreStaaGal )
                    setAnimasjon( aVenstreHeieGal );
            }
        }
    }

    Sprite::oppdaterAni( tid );
}

void Kou::hopp( bool ekstrahopp )
{
    if ( ( bakken && getYHast() >= 0 && getYHast() < 0.1 ) || ekstrahopp )
    {
        setYHast( -1 );
        bakken = false;
    }
}

void Kou::kolliderY()
{
    bakken = true;
}

void Kou::setSeier( bool s )
{
    seier = s;
}

bool Kou::getSeier() const
{
    return seier;
}

void Kou::setStatus( Status* s )
{
    status = s;
}

Ildkule* Kou::getIldkule() const
{
    double xh = 0.35;

    if ( getXHast() < 0 || getAnimasjon() == aLitenVenstreStaa || getAnimasjon() == aVenstreStaa || getAnimasjon() == aVenstreStaaGal )
        xh = -0.35;

    return new Ildkule( getX() + getLengde() / 2, getY() + getHoyde() / 2, xh, -0.3, new Animasjon( *ildkule ) );
}
