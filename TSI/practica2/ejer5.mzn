include "globals.mzn";

int: asignaturas = 9;
int: profesores = 4;
int: horas = 6;
int: dias = 5;
int: clases = horas*dias;

array[1..asignaturas] of int: horas_asignaturas = [4, 2, 4, 4, 4, 2, 2, 2, 1];
array[1..asignaturas] of int: horas_por_dia =     [2, 1, 2, 2, 2, 1, 1, 2, 1];

array[1..dias, 1..horas] of var 0..asignaturas: horario;

% 1 bloque al dia para los profesores 1, 2, 3
constraint forall(i in 1..dias, j in 1..horas)(if horario[i,j] == 1 then forall(k in 1..horas)(horario[i,k] != 2) else true endif); % prof1
constraint forall(i in 1..dias, j in 1..horas)(if horario[i,j] == 4 then forall(k in 1..horas)(horario[i,k] != 5) else true endif); % prof2
constraint forall(i in 1..dias, j in 1..horas)(if horario[i,j] == 6 then forall(k in 1..horas)(horario[i,k] != 9) else true endif); % prof3

% un bloque por dia
constraint forall(i in 1..dias, j in 1..horas)(if horas_por_dia[horario[i,j]] == 1 then sum(l in 1..horas)(if horario[i,l] == horario[i,j] then 1 else 0 endif) == 1 else true endif);
constraint forall(i in 1..dias, j in 1..horas)(if horas_por_dia[horario[i,j]] == 2 then sum(l in 1..horas)(if horario[i,l] == horario[i,j] then 1 else 0 endif) == 2 else true endif);

% bloques de 2 horas
constraint forall(i in 1..dias)(if horas_por_dia[horario[i,1]] == 2 then horario[i, 2] == horario[i,1] else true endif); % primera hora (evitar indice fuera de rango al hacer j-1)
constraint forall(i in 1..dias, j in 2..horas-1, k in 1..asignaturas)(if horario[i,j] == k /\ horas_por_dia[k] == 2 then (horario[i, j+1] == k /\ horario[i, j-1] != k) \/ (horario[i, j-1] == k /\ horario[i, j+1] != k) else true endif);

% se dan todas las horas de cada asignatura
constraint forall(i in 1..asignaturas)(sum(j in 1..dias, k in 1..horas)(if horario[j,k] == i then 1 else 0 endif) == horas_asignaturas[i]);

% recreo
constraint forall(i in 1..dias, j in 1..horas)(if j != 4 then horario[i,j] != 0 else horario[i,j] == 0 endif);

solve satisfy;

array[1..asignaturas+1] of string: nombre_clases = ["re", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9"];
output [ if i == dias+1 then "\n" else "\(nombre_clases[fix(horario[i,j])+1]) " endif | j in 1..horas, i in 1..dias+1];
