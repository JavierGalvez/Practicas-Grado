include "globals.mzn";

array[1..10] of var 0..9: numero;

constraint forall(i in 1..10)(count(numero, i-1) == numero[i]);

solve satisfy;

output ["\(numero[i])" | i in 1..10];