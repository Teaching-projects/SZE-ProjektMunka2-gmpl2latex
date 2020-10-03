# Főbb megvalósítandó funkciók

A program legyen képes az alábbi kódrészletekből álló bemeneti álllományból LateX kódot generálni:

*Változó deklarálása  kezdeti megszorításokkal
*Megszorítások deklarálása
*Célfüggvény deklarálása
*Komment sorok  ezeket be kell illeszteni magyarázó szövegként a LateX dokumentumba a megfelelő helyre ha #! karakterekkel kezdődik

A Latex kód generálása az alábbi két lépés segítségével történik:

1. A program bemenete egy szintaktikailag helyes .mod kiterjesztésű fájl;  kimenete egy szöveges szerkeszthető állomány amelyben a felhasználó meghatározhatja a kigyűjtött változók, korlátozások és a célfüggvény azonosítóinak LateX megfelelőjét.
2. A program bemenete a .mod fájl és az előző lépésben keletkezett szöveges állomány; kimenete .tex formátumú Latex fájl.

Nem funkcionális követelmények:
..*Legyen linux alatt használható.

## Bemenet .mod
~~~ampl
#######################
## VARIABLES ##########
#######################

var KF >= 0; #!< The amount of Kisfroccs we sell
var NF >= 0; #!< The amount of Nagyfroccs we sell
var HL >= 0; #!< The amount of Hosszulepes we sell


#######################
## CONSTRAINTS ########
#######################

#! This equation enforces that we don't use more than 100 l of wine.
s.t. Wine:  
    0.1*KF + 0.2*NF + 0.1*HL <= 100;


#! This is a similar constraint that limits the usage of carbonated water to 150l.
s.t. Carbonated_Water:  
    0.1*KF + 0.1*NF + 0.2*HL <= 150;

#######################
## OBJECTIVE ##########
#######################

#! The objective is to maximize the profit, with 120, 210, and 140 HUF of a price for a portion of Kisfroccs, Nagyfroccs, Hosszulepes, respectively.

maximize Profit:
    120*KF + 210*NF + 140*HL;
~~~


##Szótár
JSON kód:
~~~json
{
    "Variables" : {
        "KF" : "x_1",
        "NF" : "x_2",
        "HL" : "x_3"
    }
}
~~~

##HTML kimenet

<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <title></title>
  <meta name="author" content="">
  <meta name="description" content="">
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>


<h4>Variables</h4>

<dl>
    <dt>\(x_1\in[0,\infty[\)</dt> <dd>The amount of Kisfroccs we sell</dd>
    <dt>\(x_2\in[0,\infty[\)</dt> <dd>The amount of Nagyfroccs we sell</dd>
    <dt>\(x_3\in[0,\infty[\)</dt> <dd>The amount of Hosszulepes we sell</dd>
</dl>

<h4>Constraints</h4>

<p class="description">
    This equation enforces that we don't use more than 100 l of wine.
</p>

<p>
    \[ 0.1 \cdot x_1 + 0.2 \cdot x_2 + 0.1 \cdot x_3 \le 100 \]
</p>

<p class="description">
    This is a similar constraint that limits the usage of carbonated water to 150l.
</p>

<p>
    \[ 0.1 \cdot x_1 + 0.1 \cdot x_2 + 0.2 \cdot x_3 \le 150 \]
</p>

<h4>Objective</h4>

<p class="description">
    The objective is to maximize the profit, with 120, 210, and 140 HUF of a price for a portion of Kisfroccs, Nagyfroccs, Hosszulepes, respectively.
</p>

<p>
    \[ 120\cdot x_1 + 210\cdot x_2 + 140\cdot x_3 \to \max \]
</p>

<script src="https://cdn.jsdelivr.net/npm/mathjax@2/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>

</body>

</html>


##LateX kimenet
~~~tex
\documentclass{article}

\begin{document}

    \subsubsection*{Variables}

    \begin{description}
        \item[$x_1\in[0,\infty[$] The amount of Kisfroccs we sell
        \item[$x_2\in[0,\infty[$] The amount of Nagyfroccs we sell
        \item[$x_3\in[0,\infty[$] The amount of Hosszulepes we sell 
    \end{description}

    \subsubsection*{Constraints}

    This equation enforces that we don't use more than 100 l of wine.

    $$ 0.1 \cdot x_1 + 0.2 \cdot x_2 + 0.1 \cdot x_3 \le 100 $$

    This is a similar constraint that limits the usage of carbonated water to 150l.

    $$ 0.1 \cdot x_1 + 0.1 \cdot x_2 + 0.2 \cdot x_3 \le 150 $$

    \subsubsection*{Objective}

    The objective is to maximize the profit, with 120, 210, and 140 HUF of a price for a portion of Kisfroccs, Nagyfroccs, Hosszulepes, respectively.

    $$ 120\cdot x_1 + 210\cdot x_2 + 140\cdot x_3 \to \max $$

\end{document}
~~~

##Generált pdf
![alt text](https://github.com/Teaching-projects/SZE-ProjektMunka2-gmpl2latex/tree/master/Requirements/simple_example_output.png "Pdf output from Latex")


