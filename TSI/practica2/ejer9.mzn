include "globals.mzn";

set of int: tareas = 1..10;
int: A = 1; int: B = 2; int: C = 3; int: D = 4; int: E = 5; 
int: F = 6; int: G = 7; int: H = 8; int: I = 9; int: AUX = 10;

int: trabajadores = 3;

array[1..trabajadores, tareas] of int: duracion = 
[|4, 3, 3, 2, 4, 3, 1, 1, 2, 0
 |7, 5, 1, 5, 2, 2, 2, 3, 3, 0
 |10, 7, 4, 8, 6, 1, 3, 5, 4, 0|];
 
array[tareas] of var 1..trabajadores: trabajando;

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
constraint forall(i in 1..9)(inicio[i] >= 
max(inicio[predecesoras[i,1]] + duracion[trabajando[predecesoras[i,1]], predecesoras[i,1]], inicio[predecesoras[i,2]] + duracion[trabajando[predecesoras[i,2]], predecesoras[i,2]]));

% para empezar una tarea debe haber minimo 1 trabajador libre
constraint forall(i in 1..9)(trabajadores - sum(j in 1..9)(if inicio[j] + duracion[trabajando[j], j] > inicio[i] /\ j!=i /\ inicio[j] <= inicio[i] then 1 else 0 endif) > 0);

% un trabajador no puede hacer 2 tareas al mismo tiempo
constraint forall(i, j in 1..9)(if inicio[j] + duracion[trabajando[j], j] > inicio[i] /\ i != j /\ inicio[j] <= inicio[i] then trabajando[j] != trabajando[i] else true endif);

% acabamos la construcción cuando termina la última tarea
var int: tiempo_total = max(i in tareas)(inicio[i] + duracion[trabajando[i], i]);
 
solve minimize tiempo_total;
 
array[1..9] of string: nombre_tareas = ["Levantar muros", "Carpintería de tejado", "Poner tejado", "Instalación eléctrica", "Pintado fachada",
"Ventanas", "Jardín", "Techado", "Pintado interior"];
output ["Menor tiempo posible = \(tiempo_total) dias\n", "\nTiempo de inicio de las tareas\n"] ++ ["Tr\(trabajando[i]), \(nombre_tareas[i]) = Dia \(inicio[i])\n" | i in 1..9];