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

#include "vindu.h"

using namespace std;

Vindu::Vindu()
{
    kart = 0;
    kou = 0;
    timer = new QTimer();
    msgTimer = new QTimer();
    skadeTimer = new QTimer();
    connect( timer, SIGNAL( timeout() ), this, SLOT( update() ) );
    connect( skadeTimer, SIGNAL( timeout() ), this, SLOT( skadeOver() ) );
    status = new Status();
    fiksIntro();
}

Vindu::~Vindu()
{
    if ( kart != 0 )
        delete kart;

    delete timer;
    delete msgTimer;
    delete skadeTimer;
    delete status;
}

void Vindu::fiksIntro()
{
    timer->stop();
    bg.load( QString( "bilder/startskjerm.png" ) );
    status->setTilstand( Status::INTRO );
    status->setLiv( 4 );
    status->setBrettNr( 1 );
}

void Vindu::fiksNeste()
{
    if ( kart != 0 )
    {
        delete kart;
        kart = 0;
    }

    QFile fil( QString( "kart/kart" + QString::number( status->getBrettNr() ) + ".txt" ) );

    if ( fil.exists() )
    {
        kart = new Kart( fil.fileName() );
        bg = kart->getBakgrunn();
        status->setTilstand( Status::SPILL );
        status->setSpillTid( kart->getTid() );
        kou = kart->getKou();
        kou->setStatus( status );
        status->oppdaterTid();
        timer->start( 25 );
        update();
    }

    else
    {
        delete status;
        status = new Status();
        fiksIntro();
        status->setBrettNr( 1 );
        update();
    }
}

void Vindu::dodKou()
{
    kou->setLever( false );
    kou->setXHast( 0 );
    kou->setYHast( 0 );
    status->decLiv();

    if ( status->getLiv() > 0 )
        status->setTilstand( Status::DOD );
    else
        status->setTilstand( Status::HELTDOD );
}

void Vindu::skadeOver()
{
    status->setSkadd( false );
}

// Sjekker kollisjoner mellom vesener og klosser. Ikke så veldig elegant for øyeblikket, men fungerer greit.
// Bruker prinsippet om å sjekke om den nye posisjonen er gyldig før noe får flytte på seg.
// Da slipper jeg å fikse problemet etter at det har skjedd, og jeg slipper hakkende bevegelser ved kollisjoner.
void Vindu::sjekkKollisjon( Vesen* v, int tid )
{
    // Alle vesener må slite med tyngdekrafta.
    v->setYHast( v->getYHast() + 0.003 * tid );

    // Beveger seg mot høyre
    if ( v->getXHast() > 0 )
    {
        // For å slippe å sjekke kollisjoner med alle klossene, så finner jeg kun de som kou kan komme
        // borti ved å gå i den retningen han gjør.
        // Må også passe på å ikke lese fra ulovlige minneområder. Fort gjort!
        int nyposx = (int) ( v->getX() + v->getXHast() * tid );
        int kollikloss = ( nyposx + v->getLengde() ) / 32;
        int starty = max( 0, v->getY() / 32 );
        int stoppy = ( v->getY() + v->getHoyde() ) / 32;
        bool stopp = false;
        stoppy++;

        for ( int i = starty; i < stoppy; i++ )
        {
            // Det holder å vite at det er en kollisjon. Rad eller kolonne vet jeg allerede.
            if ( i < kart->hentHoyde() && kart->hentBredde( i ) > kollikloss && kart->hentBilde( i, kollikloss ) != 0 )
            {
                stopp = true;
                break;
            }
        }

        if ( stopp == false )
            v->setX( nyposx );

        else
        {
            v->setX( ( kollikloss * 32 ) - v->getLengde() -1 );
            v->kolliderX();
        }
    }

    // Beveger seg mot venstre
    else if ( v->getXHast() < 0 )
    {
        int nyposx = (int) ( v->getX() + v->getXHast() * tid );
        int kollikloss = nyposx / 32;
        int starty = max( 0, v->getY() / 32 );
        int stoppy = ( v->getY() + v->getHoyde() ) / 32;
        bool stopp = false;
        stoppy++;

        for ( int i = starty; i < stoppy; i++ )
        {
            if ( i < kart->hentHoyde() && kart->hentBredde( i ) > kollikloss && kart->hentBilde( i, kollikloss ) != 0 )
            {
                stopp = true;
                break;
            }
        }

        if ( stopp == false )
            v->setX( nyposx );

        else
        {
            v->setX( ( kollikloss * 32 ) + 32 );
            v->kolliderX();
        }
    }

    // Faller
    if ( v->getYHast() > 0 )
    {
        int nyposy = (int) ( v->getY() + v->getYHast() * tid );
        int kollikloss = min( max( 0, ( nyposy + v->getHoyde() ) / 32 ), kart->hentHoyde() -1 );
        int startx = v->getX() / 32;
        int stoppx = ( v->getX() + v->getLengde() ) / 32;
        bool stopp = false;
        stoppx++;

        for ( int i = startx; i < stoppx; i++ )
        {
            if ( i < kart->hentBredde( kollikloss ) && kart->hentBilde( kollikloss, i ) != 0 )
            {
                stopp = true;
                break;
            }
        }

        if ( stopp == false )
            v->setY( nyposy );

        else
        {
            v->setYHast( 0 );
            v->setY( ( kollikloss * 32 ) - v->getHoyde() -1 );
            v->kolliderY();
        }
    }

    // Hopper
    else if ( v->getYHast() < 0 )
    {
        int nyposy = (int) ( v->getY() + v->getYHast() * tid );
        int kollikloss = min( max( 0, nyposy / 32 ), kart->hentHoyde() -1 );
        int startx = v->getX() / 32;
        int stoppx = ( v->getX() + v->getLengde() ) / 32;
        bool stopp = false;
        stoppx++;

        for ( int i = startx; i < stoppx; i++ )
        {
            if ( i < kart->hentBredde( kollikloss ) && kart->hentBilde( kollikloss, i ) != 0 )
            {
                stopp = true;
                break;
            }
        }

        if ( stopp == false )
            v->setY( nyposy );

        else
        {
            v->setY( (  kollikloss * 32 ) + 32 );
            v->setYHast( v->getYHast() * -1 );
        }
    }
}

// En stor del av game loopen. Tegner, regner, og sjekker kollisjoner mellom sprites.
void Vindu::paintEvent( QPaintEvent* )
{
    QPainter painter( this );

    if ( status->getTilstand() == Status::INTRO )
        painter.drawPixmap( 0, 0, bg );

    else if ( status->getTilstand() == Status::LASTBRETT )
        fiksNeste();

    else
    {
        int brukttid = status->finnBruktTid();
        int kartbredde = kart->hentKartBredde( kart->hentHoyde() -1 );
        int offset = 0;

        // Stoppe oppdatering av kou når han faller under kanten på brettet.
        if ( kou->getY() < kart->hentKartHoyde() +50 )
        {
            kou->oppdaterPos( brukttid );
            sjekkKollisjon( kou, brukttid );
        }

        // Kou dør om han faller under kanten på brettet, eller bruker opp tida
        if ( kou->getLever() && kou->getSeier() == false && ( kou->getY() > kart->hentKartHoyde() || status->getSpillTid() <= 0 ) )
            dodKou();

        // For å holde kou på midten av skjermen, med unntak av langs kantene av brettet.
        if ( kou->getX() > 650 / 2 )
        {
            if ( kou->getX() > kartbredde - 650 / 2 )
                offset = kartbredde - 650;
            else
                offset = kou->getX() - 650 / 2;
        }

        // Bakgrunnsbildet scroller saktere, siden det er mindre enn brettet. Må finne ut hvor på bildet man skal starte å tegne.
        double bgstartpos = (double) bg.width() / ( (double) kartbredde - 650.0 ) * (double) offset / 2.0;
        painter.drawPixmap( 0, 0, bg, (int) bgstartpos, 0, 650, 450 );

        // Finne ut hvor jeg skal starte å tegne klosser, sånn at bare de synlige blir med.
        int startpos = kou->getX() - ( kou->getX() - offset );

        // Tegne klossene
        for ( int i = 0; i < kart->hentHoyde(); i++ )
        {
            for ( int j = 0; j < kart->hentBredde( i ); j++ )
            {
                QPixmap *pix = kart->hentBilde( i, j );

                if ( pix != 0 && j * 32 > startpos -32 && j * 32 < startpos + 650 )
                {
                    painter.drawPixmap( QPoint( j * 32 - offset, i * 32 ), *pix );
                    //painter.drawRect( j * 32 - offset, i * 32, 32, 32 );
                }
            }
        }

        // Fikse sprites
        for ( int i = 0; i < kart->getSprites().size(); i++ )
        {
            Sprite* s = kart->getSprites()[i];
            QPoint p = s->getPosisjon();
            QRect r = s->getRect();

            // Hvis et vesen faller under kanten på brettet så dør det.
            if ( Vesen* v = dynamic_cast<Vesen*> (s) )
            {
                if ( v->getLever() && v->getY() > kart->hentKartHoyde() )
                {
                    v->setLever( false );
                    v->setYHast( 0 );
                    v->setXHast( 0 );
                }
            }

            // Hvis kou er i kontakt med en sprite.
            if ( s->getSynlig() && kou->getLever() && !status->isSkadd() && kou->getRect().intersects( r ) )
            {
                // Og denne spriten er et farlig vesen.
                if ( FarligVesen* v = dynamic_cast<FarligVesen*> (s) )
                {
                    if ( kou->getSeier() == false && v->getLever() )
                    {
                        QRect ri = kou->getRect().intersect( r );
                        bool feiltreff = false;

                        if ( dynamic_cast<Spungy*> (v) )
                        {
                            // Sjekker om kou er borti siden av en Spungy.
                            if ( ri.width() < 5 && ri.height() > 10 )
                                feiltreff = true;
                        }

                        else if ( dynamic_cast<Goompa*> (v) )
                        {
                            // Sjekker om kou havna under en Goompa.
                            if ( ri.width() > 10 )
                            {
                                if ( kou->getY() == ri.top() )
                                    feiltreff = true;
                            }

                            // Eller traff siden.
                            else if ( ri.height() > 10 )
                                feiltreff = true;
                        }

                        if ( feiltreff )
                        {
                            // Krympe og bli uovervinnelig i et sekund, så kou ikke dør om han kommer borti
                            // 2 ganger eller fler i sammenstøtet.
                            if ( status->getStorrelse() != Status::LITEN )
                            {
                                v->kolliderX();

                                if ( status->getStorrelse() == Status::VANLIG )
                                    status->setStorrelse( Status::LITEN );
                                else if ( status->getStorrelse() == Status::GAL )
                                    status->setStorrelse( Status::VANLIG );

                                kou->oppdaterPos( 0 );
                                kou->setY( v->getY() + v->getHoyde() - kou->getHoyde() );
                                status->setSkadd( true );
                                skadeTimer->setSingleShot( true );
                                skadeTimer->start( 1000 );
                            }

                            else
                                dodKou();
                        }

                        else
                        {
                            kou->setY( r.top() - kou->getHoyde() );
                            kou->kolliderY();
                            kou->hopp( true );
                            v->setLever( false );
                            v->setXHast( 0 );
                            status->incSpungy();
                        }
                    }
                }

                else if ( Ost* o = dynamic_cast<Ost*> (s) )
                {
                    o->setSynlig( false );
                    o->setFjernes( true );
                    status->incOst();

                    if ( status->getOst() >= 40 )
                    {
                        status->setOst( 0 );
                        status->incLiv();
                        msgTimer->setSingleShot( true );
                        msgTimer->start( 1000 );
                        msg.msg = "Du fikk et ekstra liv!";
                        msg.x = 240;
                        msg.y = 180;
                    }
                }

                else if ( Banan* b = dynamic_cast<Banan*> (s) )
                {
                    b->setSynlig( false );
                    b->setFjernes( true );
                    kou->setSeier( true );
                    kou->setXHast( 0 );
                    status->setTilstand( Status::FERDIGBRETT );
                }

                else if ( SpmBoks* spm = dynamic_cast<SpmBoks*> (s) )
                {
                    if ( status->getStorrelse() == Status::VANLIG || status->getStorrelse() == Status::GAL )
                    {
                        Sprite* spmsprite = spm->getInnhold();

                        if ( Oppgradering* oppg = dynamic_cast<Oppgradering*> (spmsprite) )
                            oppg->setType( Oppgradering::REAGENSROR );
                    }

                    if ( !spm->isTruffet() )
                        spm->treff();
                }

                else if ( Oppgradering* o = dynamic_cast<Oppgradering*> (s) )
                {
                    o->setSynlig( false );
                    o->setFjernes( true );

                    if ( status->getStorrelse() == Status::LITEN )
                        status->setStorrelse( Status::VANLIG );
                    else if ( status->getStorrelse() == Status::VANLIG )
                        status->setStorrelse( Status::GAL );

                    kou->oppdaterPos( 0 );
                    kou->setY( o->getY() + o->getHoyde() - kou->getHoyde() -1 );
                }
            }

            if ( Vesen* v = dynamic_cast<Vesen*> (s) )
            {
                if ( v->getLever() )
                {
                    // Snur et vesen hvis det kommer til en av kantene på brettet som ikke har en blokkerende kloss.
                    if ( p.x() <= 0 || p.x() >= kart->hentKartBredde( kart->hentHoyde() -1 ) - v->getAnimasjon()->hentBilde().width() )
                        v->setXHast( v->getXHast() * -1 );

                    // Sjekker kollisjoner mellom vesener.
                    for ( int j = i; j < kart->getSprites().size(); j++ )
                    {
                        Sprite* tmps = kart->getSprites()[j];

                        // Sjekker kollisjoner mellom Spungyer.
                        if ( Spungy* spungytmp = dynamic_cast<Spungy*> (tmps) )
                        {
                            QRect tmpr = spungytmp->getRect();

                            if ( spungytmp != v && spungytmp->getLever() && r.intersects( tmpr ) )
                            {
                                if ( Spungy* spungy = dynamic_cast<Spungy*> (v) )
                                {
                                    spungy->setXHast( spungy->getXHast() * -1 );
                                    spungytmp->setXHast( spungytmp->getXHast() * -1 );
                                }
                            }
                        }

                        // Sjekke om en Spungy eller Goompa er truffet av en ildkule
                        if ( Ildkule* ildkuletmp = dynamic_cast<Ildkule*> (tmps) )
                        {
                            QRect tmpr = ildkuletmp->getRect();

                            if ( ildkuletmp != v && ildkuletmp->getSynlig() && r.intersects( tmpr ) )
                            {
                                bool treff = false;

                                if ( dynamic_cast<Spungy*> (v) )
                                    treff = true;
                                else if ( dynamic_cast<Goompa*> (v) )
                                    treff = true;

                                if ( treff )
                                {
                                    v->setLever( false );
                                    v->setXHast( 0 );
                                    status->incSpungy();
                                    ildkuletmp->kolliderX();
                                }
                            }
                        }
                    }
                }

                // Bare oppdatere vesener som ikke er under skjermen
                if ( v->getY() < kart->hentKartHoyde() +50 )
                {
                    sjekkKollisjon( v, brukttid );
                    v->oppdaterPos( brukttid );
                }
            }

            else
                s->oppdaterAni( brukttid );

            // Bare tegne sprites som er synlige, og justere posisjonen i forhold til kou.
            if ( s->getSynlig() && p.x() > startpos -32 && p.x() < startpos + 650 )
            {
                p.setX( p.x() - offset );
                painter.drawPixmap( p, s->getAnimasjon()->hentBilde() );
            }

            // Tegne kollisjonboks rundt alle spritene
            //r.moveLeft( r.x() - offset );
            //painter.drawRect( r );

            if ( s->getFjernes() )
            {
                kart->slettSprite( s );
                i--;
            }
        }

        int kartende = kart->hentKartBredde( kart->hentHoyde() -1 ) - kart->getKou()->getAnimasjon()->hentBilde().width();

        // Fikse så kou ikke går utenfor kartet
        if ( kou->getX() < 0 )
            kou->setX( 0 );
        else if ( kou->getX() > kartende )
            kou->setX( kartende );

        // Tegne kollisjonboks rundt kou
        //QRect r = kart->getKou()->getRect();
        //r.moveLeft( r.x() - offset );
        //painter.drawRect( r );

        // Justere posisjonen til kou før tegning, så han holder seg synlig på skjermen.
        QPoint p = kart->getKou()->getPosisjon();
        p.setX( kou->getX() - offset );
        p.setY( p.y() +2 );
        painter.drawPixmap( p, kou->getAnimasjon()->hentBilde() );

        // Tegne stripa øverst med status informasjon.
        QFont f = painter.font();
        f.setPointSize( 12 );
        painter.setFont( f );
        painter.drawPixmap( 10, 0, status->getMiniOst() );
        painter.drawText( 50, 22, QString::number( status->getOst() ) );
        painter.drawPixmap( 100, 0, status->getMiniKou() );
        painter.drawText( 150, 22, QString::number( status->getLiv() ) );
        painter.drawPixmap( 200, 0, status->getMiniSpungy() );
        painter.drawText( 255, 22, QString::number( status->getSpungy() ) );
        painter.drawText( 390, 22, "FPS: " + QString::number( status->getFPS() ) );
        painter.drawText( 480, 22, "Tid: " + QString::number( status->getSpillTid() ) );
        painter.drawText( 560, 22, "Level: " + QString::number( status->getBrettNr() ) );

        // Diverse meldinger som dukker opp på skjermen ved status endring.
        if ( status->getTilstand() == Status::DOD )
        {
            QFont f = painter.font();
            f.setPointSize( 20 );
            painter.setFont( f );
            painter.drawText( 250, 180, "Du døde..." );
            f.setPointSize( 12 );
            painter.setFont( f );
            painter.drawText( 190, 210, "Trykk 'Enter' for å prøve på nytt." );
        }

        else if ( status->getTilstand() == Status::HELTDOD )
        {
            QFont f = painter.font();
            f.setPointSize( 20 );
            painter.setFont( f );
            painter.drawText( 250, 180, "Du døde..." );
            f.setPointSize( 12 );
            painter.setFont( f );
            painter.drawText( 215, 210, "Trykk 'Enter' for å avslutte." );
        }

        else if ( status->getTilstand() == Status::FERDIGBRETT )
        {
            QFont f = painter.font();
            f.setPointSize( 20 );
            painter.setFont( f );
            painter.drawText( 240, 180, "Du redda B2!" );
            f.setPointSize( 12 );
            painter.setFont( f );
            painter.drawText( 220, 210, "Trykk 'Enter' for neste brett." );
        }

        if ( msgTimer->isActive() )
        {
            QFont f = painter.font();
            f.setPointSize( 14 );
            painter.setFont( f );
            painter.drawText( msg.x, msg.y, msg.msg );
        }
    }
}

void Vindu::keyPressEvent( QKeyEvent *event )
{
    if ( status->getTilstand() == Status::SPILL )
    {
        if ( kart->getKou()->getLever() && kart->getKou()->getSeier() == false )
        {
            if ( event->key() == Qt::Key_Left )
            {
                kart->getKou()->setXHast( -0.3 );
                event->accept();
            }

            else if ( event->key() == Qt::Key_Right )
            {
                kart->getKou()->setXHast( 0.3 );
                event->accept();
            }

            else if ( event->key() == Qt::Key_Space )
            {
                kart->getKou()->hopp();
                event->accept();
            }

            else if ( event->key() == Qt::Key_P )
            {
                status->setTilstand( Status::PAUSE );
                timer->stop();
                event->accept();
            }

            else if ( event->key() == Qt::Key_Alt )
            {
                if ( status->getStorrelse() == Status::GAL && status->isIldkuleKlar() )
                {
                    kart->settInnSprite( kou->getIldkule() );
                    event->accept();
                }
            }
        }
    }

    else if ( status->getTilstand() == Status::PAUSE )
    {
        if ( event->key() == Qt::Key_P )
        {
            status->setTilstand( Status::SPILL );
            timer->start();
            status->finnBruktTid();
            event->accept();
        }
    }

    else if ( status->getTilstand() == Status::INTRO )
    {
        if ( event->key() == Qt::Key_Return )
        {
            status->setTilstand( Status::LASTBRETT );
            update();
            event->accept();
        }
    }

    else if ( status->getTilstand() == Status::DOD )
    {
        if ( event->key() == Qt::Key_Return )
        {
            status->setTilstand( Status::LASTBRETT );
            status->setStorrelse( Status::LITEN );
            update();
            event->accept();
        }
    }

    else if ( status->getTilstand() == Status::HELTDOD )
    {
        if ( event->key() == Qt::Key_Return )
        {
            delete status;
            status = new Status();
            fiksIntro();
            update();
            event->accept();
        }
    }

    else if ( status->getTilstand() == Status::FERDIGBRETT )
    {
        if ( event->key() == Qt::Key_Return )
        {
            status->setTilstand( Status::LASTBRETT );
            status->incBrettNr();
            update();
            event->accept();
        }
    }
}

void Vindu::keyReleaseEvent( QKeyEvent *event )
{
    if ( event->key() == Qt::Key_Left || event->key() == Qt::Key_Right )
    {
        kart->getKou()->setXHast( 0 );
        event->accept();
    }
}
