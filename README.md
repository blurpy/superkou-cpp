superkou-cpp
============

-- Super Kou C++ v0.2.6

Super Kou er skrevet i C++, og bruker et rammeverk som heter Qt4 Open Source Edition. For å kompilere kildekoden så må Qt4 og gcc/g++ være installert.

Windows:
1. Last ned og installer Qt4 med MinGW (gcc for Windows) fra http://www.trolltech.com/developer/downloads/qt/windows.
2. Pakk ut kildekoden til Super Kou i en mappe.
3. Start Qt 4.x.x Command Prompt fra start menyen.
4. Naviger til mappa med kildekoden til Super Kou, og gå inn i src mappa.
5. Skriv qmake
6. Skriv make
7. Kopier mingwm10.dll, QtCore4.dll, QtGui4.dll til rota hvor superkou.exe er. De filene er å finne i bin mappa der du installerte Qt4.
8. Ferdig! Bare trykk på superkou.exe for å starte. Det er trygt å slette src mappa.

Linux:
1. Installer Qt4 og gcc/g++ via pakkesystemet.
2. Pakk ut kildekoden til Super Kou i en mappe.
3. Åpne en terminal eller konsoll.
4. Naviger til mappa med kildekoden til Super Kou, og gå inn i src mappa.
5. Skriv qmake
6. Skriv make
7. Ferdig! Skriv ./superkou på rota for å starte. Det er trygt å slette src mappa. Iconet kou.png ligger i bilder mappa, og kan brukes til snarveier.

Mac:
1. Antageligvis noe lignende Windows og Linux metoden.

Copyright (c) 2006
Christian Ihle
kontakt@usikkert.net

Kode tilgjengelig under GPL lisensen. Se fila LICENSE for lisensdetaljer.
