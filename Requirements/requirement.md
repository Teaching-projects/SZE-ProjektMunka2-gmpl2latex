# Főbb megvalósítandó funkciók

A program legyen képes az alábbi kódrészletekből álló bemeneti álllományból LateX kódot generálni:

Változó deklarálása  kezdeti megszorításokkal
Megszorítások deklarálása
Célfüggvény deklarálása
Komment sorok  ezeket be kell illeszteni magyarázó szövegként a LateX dokumentumba a megfelelő helyre ha #! karakterekkel kezdődik

A Latex kód generálása az alábbi két lépés segítségével történik:

1. A program bemenete egy szintaktikailag helyes .mod kiterjesztésű fájl;  kimenete egy szöveges szerkeszthető állomány amelyben a felhasználó meghatározhatja a kigyűjtött változók, korlátozások és a célfüggvény azonosítóinak LateX megfelelőjét.
2. A program bemenete a .mod fájl és az előző lépésben keletkezett szöveges állomány; kimenete .tex formátumú Latex fájl.

Nem funkcionális követelmények

Legyen linux alatt használható.
