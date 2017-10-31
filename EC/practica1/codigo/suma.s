.section .data
lista:    .int 1,1,123,1,1,1,1,1
          .int 1,1,1,1,432,1,1,1
          .int 1,456,1,1,1,5234,1,1
          .int 1,1,1,1,1,1,1,234
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

  mov   $1, %eax
  mov   $0, %ebx
  int   $0x80

suma:
  push  %esi        # %esi lo utilizamos como índice
  mov   $0, %eax
  mov   $0, %esi

bucle:
  add   (%ebx,%esi,4), %eax
  jnc   acarreo     # si no hay acarreo saltamos
  inc   %edx        # en caso contrario incrementamos el acarreo

acarreo:
  inc   %esi
  cmp   %esi, %ecx
  jne   bucle

  pop   %esi
  ret
