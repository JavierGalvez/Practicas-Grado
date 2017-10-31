.section .data
lista:    .int -1,-1,-1,-1,-1,-1,-1,-1
          .int -1,-1,-1,-32,-1,12,-1,-1
          .int -1,-1,-1,42,-1,-1,-1,-1
          .int -1,-1,-1,-1,-1,-1,956,-1
longlista:	.int (.-lista)/4
resultado:	.quad -1

.section .text
_start:	.global _start

  mov   $lista, %ebx
  mov   $0, %edx     # %edx lo utilizamos para el acarreo
  mov   longlista, %ecx
  call  suma

  mov   %eax, resultado
  mov   %edx, resultado+4

  # Esta linea es la unica diferencia con la suma con signo
  idiv  %ecx         # Hacemos la division con signo de EDX:EAX entre %ecx
                     # que contiene el valor de longlista

  mov   $1, %eax
  mov   $0, %ebx
  int   $0x80

suma:
  push %esi          # %esi lo utilizamos como indice
  mov $0, %eax
  mov $0, %esi

bucle:
  mov (%ebx,%esi,4), %ebp   # Movemos el entero a %ebp
  test %ebp, %ebp           # Comprobamos si es negativo
  js negativo                 # Si es negativo saltamos a "negativo"

positivo:                  # Para sumar un numero positivo
  add %ebp, %eax            # Sumamos %ebp a %eax
  adc $0, %edx               # Sumamos el acarreo (si hay) a %edx
  jmp siguiente

negativo:                  # Para sumar un numero negativo
  neg %ebp                   # Valor absoluto de %ebp
  sub %ebp, %eax            # A %eax le restamos %ebp
  sbb $0, %edx               # Restamos el debito a %edx

siguiente:
  inc %esi
  cmp %esi, %ecx
  jne bucle

  pop   %esi
  ret
