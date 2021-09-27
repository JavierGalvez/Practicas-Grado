include "globals.mzn";

int: personas = 5;
set of int: rango = 1..personas;
int: vasco = 1; int: catalan = 2; int: gallego = 3; int: navarro = 4; int: andaluz = 5;

int: roja = 1; int: verde = 2; int: blanca = 3; int: amarilla = 4; int: azul = 5;
array[rango] of var rango: casas;

int: perro = 1; int: caracoles = 2; int: zorro = 3; int: caballo = 4; int: cebra = 5;
array[rango] of var rango: animales;

int: pintor = 1; int: escultor = 2; int: diplomatico = 3; int: violinista = 4; int: medico = 5;
array[rango] of var rango: profesion;

int: te = 1; int: cafe = 2; int: leche = 3; int: zumo = 4; int: agua = 5;
array[rango] of var rango: bebida;

constraint all_different(casas);
constraint all_different(animales);
constraint all_different(profesion);
constraint all_different(bebida);

% El vasco vive en la casa roja
constraint casas[vasco] == roja;
% El catalán tiene un perro
constraint animales[catalan] == perro;
% El gallego es un pintor
constraint profesion[gallego] == pintor;
% El navarro bebe te
constraint bebida[navarro] == te;
% El de la casa verde bebe café
constraint forall(i in rango)(if casas[i] == verde then bebida[i] == cafe else true endif);
% El escultor cría caracoles
constraint forall(i in rango)(if profesion[i] == escultor then animales[i] == caracoles else true endif);
% El diplomático vive en la casa amarilla
constraint forall(i in rango)(if profesion[i] == diplomatico then casas[i] == amarilla else true endif);
% El violinista bebe zumo
constraint forall(i in rango)(if profesion[i] == violinista then bebida[i] == zumo else true endif);

array[rango] of var rango: orden_casas;
constraint all_different(orden_casas);

% El andaluz vive en la primera casa de la izquierda
constraint orden_casas[1] == casas[andaluz];
% La casa verde está al lado de la blanca y a su derecha
constraint forall(i in rango)(if orden_casas[i] == verde then orden_casas[i-1] == blanca else true endif);
% La casa del andaluz está al lado de la azul
constraint orden_casas[2] == azul;

% El zorro está en una casa al lado de la del médico
var rango: casa_medico;
constraint forall(i in rango)(if profesion[i] == medico then casa_medico == casas[i] else true endif);
% Ésta restricción produce warnings cuando i == 1 y se hace i-1 o i == 5 y se hace i+1, se intenta acceder a una posición fuera del array y el resultado se convierte en False
% la casa más a la izquierda (orden_casas[1]) no puede tener una casa a la izquierda así que ésto no afecta al resultado ya que orden_casas[0] == casa_medico sería False de todas formas
% lo mismo ocurre con la casa más a la derecha
constraint forall(i in rango)(if animales[i] == zorro then forall(j in rango)(if orden_casas[j] == casas[i] then orden_casas[j+1] == casa_medico \/ orden_casas[j-1] == casa_medico else true endif) else true endif);

% El caballo está en una casa al lado de la del diplomático
var rango: casa_diplomatico;
constraint forall(i in rango)(if profesion[i] == diplomatico then casa_diplomatico == casas[i] else true endif);
% Ésta restricción produce los mismos warnings que la restricción de antes
constraint forall(i in rango)(if animales[i] == caballo then forall(j in rango)(if orden_casas[j] == casas[i] then orden_casas[j+1] == casa_diplomatico \/ orden_casas[j-1] == casa_diplomatico else true endif) else true endif);

% En la casa central se bebe leche
constraint forall(i in rango)(if casas[i] == orden_casas[3] then bebida[i] = leche else true endif);

solve satisfy;

array[rango] of string: regiones = ["vasco", "catalan", "gallego", "navarro", "andaluz"];
output [if fix(animales[i]) == cebra then "La cebra está en casa del \(regiones[i])\n" else "" endif | i in rango] ++
       [if fix(bebida[i]) == agua then "El \(regiones[i]) bebe agua\n" else "" endif | i in rango];