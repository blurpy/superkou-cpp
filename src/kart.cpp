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

#include "kart.h"

Kart::Kart( QString url )
{
	kou = 0;
	QFile fil( url );

	if ( fil.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		QTextStream in( &fil );

		// Putter pekere til klosser inn i en 2D QList, som forestiller et 2D kart.
		for ( int i = 0; !in.atEnd(); i++ )
		{
			QString line = fil.readLine();

			// # er kommentarfelt, og $ er ekstrainformasjon om kartet. De hopper vi over nå.
			if ( line.at( 0 ) != '#' && line.at( 0 ) != '$' )
			{
				QList<QPixmap*> tmpliste;

				for ( int j = 0; j < line.size(); j++ )
				{
					tmpliste.append( finnUrl( line.at( j ).toAscii(), j, bildekart.size() ) );
				}

				bildekart.append( tmpliste );
			}

			else if ( line.at( 0 ) == '$' )
			{
				if ( line.startsWith( "$bakgrunn" ) )
				{
					QString bg = line.remove( "$bakgrunn=" );
					bg = bg.remove( "\n" );
					bakgrunn.load( bg );
				}

				else if ( line.startsWith( "$tid" ) )
				{
					QString bg = line.remove( "$tid=" );
					bg = bg.remove( "\n" );
					tid = bg.toInt();
				}
			}
		}
	}

	fil.close();
}

Kart::~ Kart()
{
	foreach ( QPixmap* value, bildeoversikt )
		delete value;

	for ( int i = 0; i < sprites.size(); i++ )
		delete sprites[i];

	if ( kou != 0 )
		delete kou;
}

QPixmap* Kart::finnUrl( char tegn, int x, int y )
{
	// Legger kun 1 peker til hver unike kloss i lista, siden de ikke har noen tilstand. Sparer minne.
	if ( !bildeoversikt.contains( tegn ) )
	{
		switch ( tegn )
		{
			case 'A' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_div.png" ) );
				   break;
			case 'B' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_jord.png" ) );
				   break;
			case 'C' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_topp.png" ) );
				   break;
			case 'D' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_venstre.png" ) );
				   break;
			case 'E' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_venstre_kant.png" ) );
				   break;
			case 'F' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_venstre_hjorne.png" ) );
				   break;
			case 'G' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_hoyre.png" ) );
				   break;
			case 'H' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_hoyre_kant.png" ) );
				   break;
			case 'I' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gress_hoyre_hjorne.png" ) );
				   break;
			case 'J' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun.png" ) );
				   break;
			case 'K' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_topp.png" ) );
				   break;
			case 'L' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_venstre.png" ) );
				   break;
			case 'M' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre.png" ) );
				   break;
			case 'N' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_bunn.png" ) );
				   break;
			case 'O' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_venstre_bunn.png" ) );
				   break;
			case 'P' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_kant_hoyre_topp.png" ) );
				   break;
			case 'Q' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_topp.png" ) );
				   break;
			case 'R' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_venstre_topp.png" ) );
				   break;
			case 'S' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_kant_venstre_topp.png" ) );
				   break;
			case 'T' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_topp_venstre.png" ) );
				   break;
			case 'U' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_topp_bunn.png" ) );
				   break;
			case 'V' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_venstre_topp_bunn.png" ) );
				   break;
			case 'W' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_topp_bunn.png" ) );
				   break;
			case 'X' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_topp_bunn_venstre.png" ) );
				   break;
			case 'Y' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_bunn.png" ) );
				   break;
			case 'Z' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_kant_hoyre_bunn.png" ) );
				   break;
			case '1' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_kant_topp_venstre.png" ) );
				   break;
			case '2' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_venstre_kant_topp_hoyre.png" ) );
				   break;
			case '3' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_hoyre_venstre.png" ) );
				   break;
			case '4' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_brun_kant_venstre_bunn.png" ) );
				   break;
			case '0' : bildeoversikt.insert( tegn, new QPixmap( "bilder/kloss_gronn.png" ) );
				   break;
			case 'f' : bildeoversikt.insert( tegn, new QPixmap( "bilder/placebo.png" ) );
				   break;
			case 'x' : bildeoversikt.insert( tegn, new QPixmap( "bilder/placebo.png" ) );
				   break;
			default  : break;
		}
	}

	// Lager sprites. Her er det en ny for hver gang, siden de har en tilstand.
	switch ( tegn )
	{
		case 's' : lagSpungy( x * 32, ( y * 32 ) -13 );
			   break;
		case 'o' : lagOst( x * 32, y * 32 );
			   break;
		case 'k' : lagKou( x * 32, ( y * 32 ) -59 );
			   break;
		case 'b' : lagBanan( x * 32, ( y * 32 ) -21 );
			   break;
		case 'f' : lagOppgradering( x * 32, y * 32 );
			   break;
		case 'g' : lagGoompa( x * 32, y * 32 );
			   break;
		case 'x' : lagBoksOst( x * 32, y * 32 );
			   break;
		default  : break;
	}

	return bildeoversikt[tegn];
}

QPixmap* Kart::hentBilde( int x, int y ) const
{
	return bildekart[x][y];
}

int Kart::hentHoyde() const
{
	return bildekart.size();
}

int Kart::hentBredde( int x ) const
{
	return bildekart[x].size();
}

int Kart::hentKartHoyde() const
{
	return bildekart.size() * 32;
}

int Kart::hentKartBredde( int x ) const
{
	return bildekart[x].size() * 32;
}

Kou* Kart::getKou() const
{
	return kou;
}

const QList<Sprite*> &Kart::getSprites() const
{
	return sprites;
}

void Kart::lagBanan( int x, int y )
{
	Animasjon* a = new Animasjon();
	a->leggTilBilde( QPixmap( "bilder/banan1.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/banan2.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/banan3.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/banan2.png" ), 200 );

	sprites.append( new Banan( x, y, a ) );
}

void Kart::lagOppgradering( int x, int y )
{
	Animasjon* ny = new Animasjon();
	Animasjon* brukt = new Animasjon();
	Animasjon* kraftfor = new Animasjon();
	Animasjon* reagensror = new Animasjon();

	QPixmap nyboks( "bilder/boks_spm.png" );
	QPixmap bruktboks( "bilder/boks_spm_brukt.png" );
	QPixmap kraftforbilde( "bilder/kraftfor.png" );
	QPixmap reagensrorbilde( "bilder/reagensror.png" );

	ny->leggTilBilde( nyboks, 20000 );
	brukt->leggTilBilde( bruktboks, 20000 );
	kraftfor->leggTilBilde( kraftforbilde, 20000 );
	reagensror->leggTilBilde( reagensrorbilde, 20000 );

	Oppgradering *o = new Oppgradering( x, y -32, kraftfor, reagensror );
	sprites.append( o );
	sprites.append( new SpmBoks( x, y, ny, brukt, o ) );
}

void Kart::lagBoksOst( int x, int y )
{
	Animasjon* ny = new Animasjon();
	Animasjon* brukt = new Animasjon();
	Animasjon* ost = new Animasjon();

	QPixmap nyboks( "bilder/boks_spm.png" );
	QPixmap bruktboks( "bilder/boks_spm_brukt.png" );

	ny->leggTilBilde( nyboks, 20000 );
	brukt->leggTilBilde( bruktboks, 20000 );

	ost->leggTilBilde( QPixmap( "bilder/ost1_mini.png" ), 200 );
	ost->leggTilBilde( QPixmap( "bilder/ost2_mini.png" ), 200 );
	ost->leggTilBilde( QPixmap( "bilder/ost3_mini.png" ), 200 );
	ost->leggTilBilde( QPixmap( "bilder/ost2_mini.png" ), 200 );

	Ost *o = new Ost( x, y -32, ost );
	sprites.append( o );
	sprites.append( new SpmBoks( x, y, ny, brukt, o ) );
}

void Kart::lagKou( int x, int y )
{
	// I tilfelle kou skulle være definert flere steder på kartet, så slipper vi minnelekasje.
	if ( kou != 0 )
		delete kou;

	Animasjon* aVGaa = new Animasjon();
	Animasjon* aVStaa = new Animasjon();
	Animasjon* aVHeie = new Animasjon();
	Animasjon* aVDod = new Animasjon();
	Animasjon* aHGaa = new Animasjon();
	Animasjon* aHStaa = new Animasjon();
	Animasjon* aHHeie = new Animasjon();
	Animasjon* aHDod = new Animasjon();

	QPixmap b1Hoyre( "bilder/kou_bak.png" );
	QPixmap b2Hoyre( "bilder/kou_midten.png" );
	QPixmap b3Hoyre( "bilder/kou_forran.png" );

	QPixmap b2HoyreHeie( "bilder/kou_heie2.png" );
	QPixmap b3HoyreHeie( "bilder/kou_heie3.png" );

	QImage q1Hoyre = b1Hoyre.toImage();
	QImage q2Hoyre = b2Hoyre.toImage();
	QImage q3Hoyre = b3Hoyre.toImage();

	QImage q2HoyreHeie = b2HoyreHeie.toImage();
	QImage q3HoyreHeie = b3HoyreHeie.toImage();

	aHGaa->leggTilBilde( b1Hoyre, 200 );
	aHGaa->leggTilBilde( b2Hoyre, 200 );
	aHGaa->leggTilBilde( b3Hoyre, 200 );
	aHGaa->leggTilBilde( b2Hoyre, 200 );

	aHStaa->leggTilBilde( b2Hoyre, 20000 );
	aHDod->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( false, true ) ), 20000 );

	aHHeie->leggTilBilde( b2Hoyre, 200 );
	aHHeie->leggTilBilde( b2HoyreHeie, 200 );
	aHHeie->leggTilBilde( b3HoyreHeie, 200 );
	aHHeie->leggTilBilde( b2HoyreHeie, 200 );

	aVGaa->leggTilBilde( QPixmap::fromImage( q1Hoyre.mirrored( true, false ) ), 200 );
	aVGaa->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( true, false ) ), 200 );
	aVGaa->leggTilBilde( QPixmap::fromImage( q3Hoyre.mirrored( true, false ) ), 200 );
	aVGaa->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( true, false ) ), 200 );

	aVStaa->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( true, false ) ), 200 );
	aVDod->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( true, true ) ), 20000 );

	aVHeie->leggTilBilde( QPixmap::fromImage( q2Hoyre.mirrored( true, false ) ), 200 );
	aVHeie->leggTilBilde( QPixmap::fromImage( q2HoyreHeie.mirrored( true, false ) ), 200 );
	aVHeie->leggTilBilde( QPixmap::fromImage( q3HoyreHeie.mirrored( true, false ) ), 200 );
	aVHeie->leggTilBilde( QPixmap::fromImage( q2HoyreHeie.mirrored( true, false ) ), 200 );

	Animasjon* aLitenVGaa = new Animasjon();
	Animasjon* aLitenVStaa = new Animasjon();
	Animasjon* aLitenVHeie = new Animasjon();
	Animasjon* aLitenVDod = new Animasjon();
	Animasjon* aLitenHGaa = new Animasjon();
	Animasjon* aLitenHStaa = new Animasjon();
	Animasjon* aLitenHHeie = new Animasjon();
	Animasjon* aLitenHDod = new Animasjon();

	QPixmap b1LitenHoyre( "bilder/mini_kou_bak.png" );
	QPixmap b2LitenHoyre( "bilder/mini_kou_midten.png" );
	QPixmap b3LitenHoyre( "bilder/mini_kou_forran.png" );

	QPixmap b2LitenHoyreHeie( "bilder/mini_kou_heie2.png" );
	QPixmap b3LitenHoyreHeie( "bilder/mini_kou_heie3.png" );

	QImage q1LitenHoyre = b1LitenHoyre.toImage();
	QImage q2LitenHoyre = b2LitenHoyre.toImage();
	QImage q3LitenHoyre = b3LitenHoyre.toImage();

	QImage q2LitenHoyreHeie = b2LitenHoyreHeie.toImage();
	QImage q3LitenHoyreHeie = b3LitenHoyreHeie.toImage();

	aLitenHGaa->leggTilBilde( b1LitenHoyre, 180 );
	aLitenHGaa->leggTilBilde( b2LitenHoyre, 180 );
	aLitenHGaa->leggTilBilde( b3LitenHoyre, 180 );
	aLitenHGaa->leggTilBilde( b2LitenHoyre, 180 );

	aLitenHStaa->leggTilBilde( b2LitenHoyre, 20000 );
	aLitenHDod->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( false, true ) ), 20000 );

	aLitenHHeie->leggTilBilde( b2LitenHoyre, 180 );
	aLitenHHeie->leggTilBilde( b2LitenHoyreHeie, 180 );
	aLitenHHeie->leggTilBilde( b3LitenHoyreHeie, 180 );
	aLitenHHeie->leggTilBilde( b2LitenHoyreHeie, 180 );

	aLitenVGaa->leggTilBilde( QPixmap::fromImage( q1LitenHoyre.mirrored( true, false ) ), 180 );
	aLitenVGaa->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( true, false ) ), 180 );
	aLitenVGaa->leggTilBilde( QPixmap::fromImage( q3LitenHoyre.mirrored( true, false ) ), 180 );
	aLitenVGaa->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( true, false ) ), 180 );

	aLitenVStaa->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( true, false ) ), 20000 );
	aLitenVDod->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( true, true ) ), 20000 );

	aLitenVHeie->leggTilBilde( QPixmap::fromImage( q2LitenHoyre.mirrored( true, false ) ), 180 );
	aLitenVHeie->leggTilBilde( QPixmap::fromImage( q2LitenHoyreHeie.mirrored( true, false ) ), 180 );
	aLitenVHeie->leggTilBilde( QPixmap::fromImage( q3LitenHoyreHeie.mirrored( true, false ) ), 180 );
	aLitenVHeie->leggTilBilde( QPixmap::fromImage( q2LitenHoyreHeie.mirrored( true, false ) ), 180 );

	Animasjon* aVGaaGal = new Animasjon();
	Animasjon* aVStaaGal = new Animasjon();
	Animasjon* aVHeieGal = new Animasjon();
	Animasjon* aVDodGal = new Animasjon();
	Animasjon* aHGaaGal = new Animasjon();
	Animasjon* aHStaaGal = new Animasjon();
	Animasjon* aHHeieGal = new Animasjon();
	Animasjon* aHDodGal = new Animasjon();

	QPixmap b1HoyreGal( "bilder/kou_bak_gal.png" );
	QPixmap b2HoyreGal( "bilder/kou_midten_gal.png" );
	QPixmap b3HoyreGal( "bilder/kou_forran_gal.png" );

	QPixmap b2HoyreHeieGal( "bilder/kou_heie2_gal.png" );
	QPixmap b3HoyreHeieGal( "bilder/kou_heie3_gal.png" );

	QImage q1HoyreGal = b1HoyreGal.toImage();
	QImage q2HoyreGal = b2HoyreGal.toImage();
	QImage q3HoyreGal = b3HoyreGal.toImage();

	QImage q2HoyreHeieGal = b2HoyreHeieGal.toImage();
	QImage q3HoyreHeieGal = b3HoyreHeieGal.toImage();

	aHGaaGal->leggTilBilde( b1HoyreGal, 200 );
	aHGaaGal->leggTilBilde( b2HoyreGal, 200 );
	aHGaaGal->leggTilBilde( b3HoyreGal, 200 );
	aHGaaGal->leggTilBilde( b2HoyreGal, 200 );

	aHStaaGal->leggTilBilde( b2HoyreGal, 20000 );
	aHDodGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( false, true ) ), 20000 );

	aHHeieGal->leggTilBilde( b2HoyreGal, 200 );
	aHHeieGal->leggTilBilde( b2HoyreHeieGal, 200 );
	aHHeieGal->leggTilBilde( b3HoyreHeieGal, 200 );
	aHHeieGal->leggTilBilde( b2HoyreHeieGal, 200 );

	aVGaaGal->leggTilBilde( QPixmap::fromImage( q1HoyreGal.mirrored( true, false ) ), 200 );
	aVGaaGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( true, false ) ), 200 );
	aVGaaGal->leggTilBilde( QPixmap::fromImage( q3HoyreGal.mirrored( true, false ) ), 200 );
	aVGaaGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( true, false ) ), 200 );

	aVStaaGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( true, false ) ), 200 );
	aVDodGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( true, true ) ), 20000 );

	aVHeieGal->leggTilBilde( QPixmap::fromImage( q2HoyreGal.mirrored( true, false ) ), 200 );
	aVHeieGal->leggTilBilde( QPixmap::fromImage( q2HoyreHeieGal.mirrored( true, false ) ), 200 );
	aVHeieGal->leggTilBilde( QPixmap::fromImage( q3HoyreHeieGal.mirrored( true, false ) ), 200 );
	aVHeieGal->leggTilBilde( QPixmap::fromImage( q2HoyreHeieGal.mirrored( true, false ) ), 200 );

	Animasjon* ildkule = new Animasjon();

	QPixmap ildkule_oh( "bilder/ildkule_oh.png" );
	QPixmap ildkule_nh( "bilder/ildkule_nh.png" );
	QPixmap ildkule_ov( "bilder/ildkule_ov.png" );
	QPixmap ildkule_nv( "bilder/ildkule_nv.png" );

	ildkule->leggTilBilde( ildkule_oh, 100 );
	ildkule->leggTilBilde( ildkule_nh, 100 );
	ildkule->leggTilBilde( ildkule_nv, 100 );
	ildkule->leggTilBilde( ildkule_ov, 100 );

	kou = new Kou( x, y, aVGaa, aVStaa, aVHeie, aVDod, aHGaa, aHStaa, aHHeie, aHDod, aLitenVGaa, aLitenVStaa, aLitenVHeie, aLitenVDod, aLitenHGaa, aLitenHStaa, aLitenHHeie, aLitenHDod, aVGaaGal, aVStaaGal, aVHeieGal, aVDodGal, aHGaaGal, aHStaaGal, aHHeieGal, aHDodGal, ildkule );
}

void Kart::lagOst( int x, int y )
{
	Animasjon* a = new Animasjon();
	a->leggTilBilde( QPixmap( "bilder/ost1_mini.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/ost2_mini.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/ost3_mini.png" ), 200 );
	a->leggTilBilde( QPixmap( "bilder/ost2_mini.png" ), 200 );

	sprites.append( new Ost( x, y, a ) );
}

void Kart::lagGoompa( int x, int y )
{
	Animasjon* hoppe = new Animasjon();
	Animasjon* dod = new Animasjon();

	QPixmap rett( "bilder/goompa_rett.png" );
	QPixmap midt( "bilder/goompa_midt.png" );
	QPixmap helt( "bilder/goompa_helt.png" );

	QImage qrett = rett.toImage();

	hoppe->leggTilBilde( rett, 120 );
	hoppe->leggTilBilde( midt, 120 );
	hoppe->leggTilBilde( helt, 120 );

	dod->leggTilBilde( QPixmap::fromImage( qrett.mirrored( false, true ) ), 20000 );

	sprites.append( new Goompa( x, y, 0.0, 0.0, hoppe, dod ) );
}


void Kart::lagSpungy( int x, int y )
{
	Animasjon* aVGaa = new Animasjon();
	Animasjon* aVDod = new Animasjon();
	Animasjon* aHGaa = new Animasjon();
	Animasjon* aHDod = new Animasjon();

	QPixmap b1Venstre( "bilder/spungy_midt.png" );
	QPixmap b2Venstre( "bilder/spungy_hoyre.png" );
	QPixmap b3Venstre( "bilder/spungy_venstre.png" );

	QImage q1Venstre = b1Venstre.toImage();
	QImage q2Venstre = b2Venstre.toImage();
	QImage q3Venstre = b3Venstre.toImage();

	aVGaa->leggTilBilde( b1Venstre, 180 );
	aVGaa->leggTilBilde( b2Venstre, 180 );
	aVGaa->leggTilBilde( b1Venstre, 180 );
	aVGaa->leggTilBilde( b3Venstre, 180 );

	aHGaa->leggTilBilde( QPixmap::fromImage( q1Venstre.mirrored( true, false ) ), 180 );
	aHGaa->leggTilBilde( QPixmap::fromImage( q2Venstre.mirrored( true, false ) ), 180 );
	aHGaa->leggTilBilde( QPixmap::fromImage( q1Venstre.mirrored( true, false ) ), 180 );
	aHGaa->leggTilBilde( QPixmap::fromImage( q3Venstre.mirrored( true, false ) ), 180 );

	aVDod->leggTilBilde( QPixmap::fromImage( q1Venstre.mirrored( false, true ) ), 20000 );
	aHDod->leggTilBilde( QPixmap::fromImage( q1Venstre.mirrored( true, true ) ), 20000 );

	sprites.append( new Spungy( x, y, 0.09, 0.0, aVGaa, aVDod, aHGaa, aHDod ) );
}

const QPixmap &Kart::getBakgrunn() const
{
	return bakgrunn;
}

int Kart::getTid() const
{
	return tid;
}

void Kart::settInnSprite( Sprite* s )
{
	sprites.append( s );
}

void Kart::slettSprite( Sprite* s )
{
	int pos = sprites.indexOf( s );
	sprites.removeAt( pos );
	delete s;
}
