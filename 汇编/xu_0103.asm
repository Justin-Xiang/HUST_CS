.386     
DATA SEGMENT USE16
lpFmt	db	0ah, 0dh, "$"
  X   DB  10, 255, -1
  Y   DW  10, 255, -1
  Z   DD  10, 255, -1
  U   DW  ($-Z)/4
  STR1 DB 'Good', 0
  P   DD  X,  Y
  Q   DB   2 DUP (5, 6)
  buf1 DB  '00123456789','$'  ;结束符号为$
  buf2 DB  12 dup(0)   
DATA ENDS
STACK  SEGMENT  USE16  STACK
   DB  200 DUP(0)
STACK  ENDS
CODE  SEGMENT  USE16
   ASSUME  CS:CODE,SS:STACK,DS:DATA
START: MOV  AX,DATA
       MOV  DS,AX
   MOV  ESI,OFFSET buf1
   MOV  EDI,OFFSET buf2 
   MOV  ECX,0
L1:
   MOV  EAX, [ESI]  
   MOV  [EDI],EAX
   ADD  ESI, 4
   ADD  EDI, 4
   ADD  ECX, 4
   CMP  ECX,12
   JNZ  L1
   MOV  DX, OFFSET buf1   ;采用DOS功能调用显示字符串
   MOV  AH,9
   INT   21H
MOV  DX, OFFSET  lpFmt
   MOV  AH,9
   INT   21H
   MOV  DX, OFFSET buf2
   MOV  AH,9
   INT   21H
   MOV AH,4CH
   INT  21H
CODE ENDS
  END START
