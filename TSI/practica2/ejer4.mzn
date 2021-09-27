include "globals.mzn";

int: asignaturas = 3;
int: grupos = 4;
int: clases = asignaturas*grupos;
int: profesores = 4;
int: horas = 4;
int: aulas = 4;

array[1..grupos, 1..clases] of int: mismo_grupo = 
% IA-G1 IA-G2 IA-G3 IA-G4 TSI-G1 TSI-G2 TSI-G3 TSI-G4 FBD-G1 FBD-G2 FBD-G3 FBD-G4
 [|1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0
  |0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0
  |0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0
  |0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1|];
  
array[1..profesores, 1..clases] of int: profesor_clase = 
% IA-G1 IA-G2 IA-G3 IA-G4 TSI-G1 TSI-G2 TSI-G3 TSI-G4 FBD-G1 FBD-G2 FBD-G3 FBD-G4
 [|1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0
  |0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
  |0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1
  |0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0|];

array[1..clases, 1..horas] of var 0..1: horario;

% no puede haber dos clases impartidas al mismo grupo a la misma hora
constraint forall(i in 1..grupos, j, k in 1..clases where j < k)(if mismo_grupo[i, j] == 1 /\ mismo_grupo[i,k] == 1 then forall(l in 1..horas)(horario[j,l]+horario[k,l] <= 1) else true endif);
% un profesor no puede dar dos clases al mismo tiempo
constraint forall(i in 1..profesores, j, k in 1..clases where j < k)(if profesor_clase[i,j] == 1 /\ profesor_clase[i,k] == 1
then forall(h in 1..horas)(horario[j,h]+horario[k,h]<=1) else true endif);
% máximo 4 clases a la misma hora
constraint forall(i in 1..horas)(sum(j in 1..clases)(horario[j,i]) <= aulas);
% prof4 no disponible de 9:00 a 10:00
constraint forall(i in 1..clases)(if profesor_clase[4, i] == 1 then horario[i, 1] = 0 else true endif);
% prof2 no disponible de 10:00 a 11:00
constraint forall(i in 1..clases)(if profesor_clase[2, i] == 1 then horario[i, 2] = 0 else true endif);

% se tienen que dar todas las clases solo una vez
constraint sum(horario) == clases;
constraint forall(i in 1..clases)(sum(j in 1..horas)(horario[i, j]) == 1);

solve satisfy;

array[1..clases] of string: nombre_clases = ["IA-G1", "IA-G2", "IA-G3", "IA-G4", 
"TSI-G1", "TSI-G2", "TSI-G3", "TSI-G4", "FBD-G1", "FBD-G2", "FBD-G3", "FBD-G4"];
array[1..horas] of string: formato_horas = ["9:00-10:00", "10:00-11:00", "11:00-12:00", "12:00-13:00"];
output [ if fix(horario[i,j]) == 1 then "clase \(nombre_clases[i]) hora \(formato_horas[j])\n" else "" endif | i in 1..clases, j in 1..horas];