
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

#ifndef VINDU_H
#define VINDU_H

#include "kart.h"
#include "status.h"

struct Melding
{
    int x;
    int y;
    QString msg;
};

class Vindu : public QWidget
{
    Q_OBJECT

    public:
        Vindu();
        ~Vindu();

    private:
        QPixmap bg;
        Kart* kart;
        Kou* kou;
        QTimer *timer, *msgTimer, *skadeTimer;
        Status* status;
        Melding msg;
        void sjekkKollisjon( Vesen* v, int tid );
        void fiksIntro();
        void fiksNeste();
        void dodKou();

    private slots:
        void skadeOver();

    protected:
        void paintEvent( QPaintEvent* event );
        void keyPressEvent( QKeyEvent* event );
        void keyReleaseEvent( QKeyEvent* event );
};

#endif
