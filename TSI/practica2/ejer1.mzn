include "globals.mzn";

array[1..10] of string: letras = ["F", "E", "S", "T", "D", "I", "N", "K", "R", "A"];
array[1..10] of var 0..9: valores;
array[1..5] of var int: acarreos;


constraint all_different(valores);

% cálculo de los acarreos
constraint acarreos[1] == ((valores[2]+valores[2]+valores[2]) / 10) - ((valores[2]+valores[2]+valores[2]) mod 10)/10;
constraint acarreos[2] == ((valores[4]+valores[4]+valores[7]+acarreos[1]) / 10) - ((valores[4]+valores[4]+valores[7]+acarreos[1]) mod 10)/10;
constraint acarreos[3] == ((valores[3]+valores[3]+valores[6]+acarreos[2]) / 10) - ((valores[3]+valores[3]+valores[6]+acarreos[2]) mod 10)/10;
constraint acarreos[4] == ((valores[2]+valores[2]+valores[2]+acarreos[3]) / 10) - ((valores[2]+valores[2]+valores[2]+acarreos[3]) mod 10)/10;
constraint acarreos[5] == ((valores[4]+valores[1]+valores[5]+acarreos[4]) / 10) - ((valores[4]+valores[1]+valores[5]+acarreos[4]) mod 10)/10;

% cálculo de cada suma
constraint (valores[2]+valores[2]+valores[2]) mod 10 == valores[2];
constraint (valores[4]+valores[4]+valores[7]+acarreos[1]) mod 10 == valores[4];
constraint (valores[3]+valores[3]+valores[6]+acarreos[2]) mod 10 == valores[1];
constraint (valores[2]+valores[2]+valores[2]+acarreos[3]) mod 10 == valores[10];
constraint (valores[4]+valores[1]+valores[5]+acarreos[4]) mod 10 == valores[9];
constraint acarreos[5] == valores[8];

solve satisfy;
output ["\(letras[i]) = \(valores[i])\n" | i in 1..10];