include "globals.mzn";

set of int: objetos = 1..12;
int: maximo = 275;

array[objetos] of int: pesos = [9, 13, 153, 50, 15, 68, 27, 39, 23, 52, 11, 32];
array[objetos] of int: preferencia = [150, 35, 200, 160, 60, 45, 60, 40, 30, 10, 70, 30];
array[objetos] of var 0..1: seleccionados;

% no podemos pasarnos del peso máximo
var int: peso_total = sum(i in objetos)(pesos[i]*seleccionados[i]);
constraint peso_total <= maximo;

% maximizamos la preferencia
var int: preferencia_total = sum(i in objetos)(preferencia[i]*seleccionados[i]);
solve maximize preferencia_total;

array[objetos] of string: nombres = ["Mapa", "Compás", "Agua", "Sandwich", "Azúcar", 
"Lata", "Plátano", "Manzana", "Queso", "Cerveza", "Protector Solar", "Cámara",];
output ["Preferencia total = \(preferencia_total)\n","Peso total = \(peso_total)\n", "\nObjetos en la mochila\n"] ++ 
       [if fix(seleccionados[i]) == 1 then "\(nombres[i])\n" else "" endif | i in objetos];