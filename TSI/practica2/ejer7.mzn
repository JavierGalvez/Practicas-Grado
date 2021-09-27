include "globals.mzn";

set of int: tareas = 1..10;
int: A = 1; int: B = 2; int: C = 3; int: D = 4; int: E = 5; 
int: F = 6; int: G = 7; int: H = 8; int: I = 9; int: AUX = 10;

array[tareas] of int: duracion = [7, 3, 1, 8, 2, 1, 1, 3, 2, 0];

array[1..9, 1..2] of tareas: predecesoras = 
[|AUX, AUX
 |A, AUX
 |B, AUX
 |A, AUX
 |C, D
 |C, D
 |C, D
 |A, AUX
 |F, H|];
 

array[tareas] of var int: inicio;
constraint forall(i in tareas)(inicio[i] >= 0);

% una tarea no empieza hasta que acaben todas las predecesoras
constraint forall(i in 1..9)(inicio[i] >= max(inicio[predecesoras[i,1]] + duracion[predecesoras[i,1]], inicio[predecesoras[i,2]] + duracion[predecesoras[i,2]]));

% acabamos la construcción cuando termina la última tarea
var int: tiempo_total = max(i in tareas)(inicio[i] + duracion[i]);
 
solve minimize tiempo_total;
 
array[1..9] of string: nombre_tareas = ["Levantar muros", "Carpintería de tejado", "Poner tejado", "Instalación eléctrica", "Pintado fachada",
"Ventanas", "Jardín", "Techado", "Pintado interior"];
output ["Menor tiempo posible = \(tiempo_total) dias\n", "\nTiempo de inicio de las tareas\n"] ++ ["\(nombre_tareas[i]) = Dia \(inicio[i])\n" | i in 1..9];