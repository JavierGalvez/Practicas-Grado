include "globals.mzn";

array[1..6, 1..2] of int: horarios = 
  [|11, 15
   |11, 13
   |10, 14
   |10, 13
   |11, 13
   |9, 15|];

array[1..6] of var 1..6: asignacion;
constraint all_different(asignacion);

% la hora a la que acaba la clase está en el intervalo (inicio, fin]
constraint forall(i in 1..6)((horarios[asignacion[i],1] < 9+i) /\ (9+i <= horarios[asignacion[i],2]));

solve satisfy;

output ["Prof-\(asignacion[i])\n" | i in 1..6];