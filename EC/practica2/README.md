# Práctica 2: Programación mixta C-asm x86 linux

## Objetivos de la práctica

* Usar las herramientas gcc, as, y ld para compilar código en C, ensamblar código ASM,
enlazar ambos tipos de código objeto, estudiar el código ensamblador generado por gcc con y sin
optimizaciones, localizar el código ASM en-línea introducido por el programador, y estudiar el
correcto interfaz del mismo con el resto del programa C.
* Reconocer la estructura del código generado por gcc según convención de la llamada cdecl.
* Reproducir dicha estructura llamando a funciones C desde programa ASM, y recibiendo llamadas
desde programa C a subrutinas ASM.
* Escribir fragmentos sencillos de ensamblador en-línea.
* Usar la instrucción CALL (con convención cdecl) desde programas ASM para hacer llamadas al
sistema operativo (kernel Linux, sección 2) y a la librería C (sección 3 del manual).
* Enumerar los registros y algunas instrucciones de los repertorios MMX/SSE de la línea x86.
* Usar con efectividad un depurador gcc/ddd.
* Argumentar la utilidad de los depuradores para ahorrar tiempo de depuración.
* Explicar la convención de llamada cdecl para procesadores x86.
* Recordar y practicar en una plataforma de 32bits las operaciones de cálculo de paridad,
cálculo de peso Hamming (population count), suma lateral (de bits o de componentes SIMD enteros)
y producto de matrices.
