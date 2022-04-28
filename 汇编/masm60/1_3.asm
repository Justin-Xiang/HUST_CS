.386
STACK 	SEGMENT	USE16 STACK
		DB 200 DUP(0)
STACK 	ENDS
DATA	SEGMENT USE16

MENUT	DB 'Please Enter a Number(1~9):$'

INNAMET	DB 'User Name:$'
WRONGNAMET DB 'Invalid User Name$'
INNAME	DB 10
		DB ?
		DB 10 DUP(0)
INPWDT	DB 'Password:$'
WRONGPWDT DB 'Invalid Password$'
INPWD	DB 10
		DB ?
		DB 10 DUP(0)
LOGINST DB 'Login in$'
INGOODT DB 'Good Name:$'
WRONGGOODT DB 'Invalid Good Name$'
INGOOD	DB 10
		DB ?
		DB 10 DUP(0)
CHANGEGOODT DB 'Good Selected$'
NOGOODT	DB 'No Goods$'
SELLGOODT DB 'Good Sold$'
NOTSELEVTEDT DB 'No Goods Selected$'
UPDATEPRIOT DB 'Priority Updated$'
BNAME  	DB 'LIAOXIANG', 0			;�ϰ�����
BPASS  	DB 'U201915116', 0				;����
AUTH   	DB 0	              		;��ǰ��¼״̬��0��ʾ�˿�״̬
GOOD   	DW 0          				;��ǰ�����Ʒ��ַ
N		EQU	30
SNAME	DB 'SHOP', 0               	;�������ƣ���0����
GA1   	DB 'PEN', 7 DUP(0), 10  	;��Ʒ���Ƽ��ۿ�
		DW 35, 56, 70, 25, ? 	 	;�����ۣ����ۼۣ����������������������Ƽ���
GA2   	DB 'BOOK', 6 DUP(0), 9  	;��Ʒ���Ƽ��ۿ�
		DW  12, 30, 25, 5, ?      	;�Ƽ��Ȼ�δ����
GAN   	DB N-2 DUP( 'TempValue' , 0, 8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
									;������ƷĬ��ֵ
CRLF	DB 0DH, 0AH, '$'			;�س�
A		DB 'A$'						;������
B		DB 'B$'
DATA	ENDS

CODE 	SEGMENT USE16
		ASSUME CS:CODE, DS:DATA, SS:STACK
START:	MOV AX, DATA				;����ʼ
		MOV DS, AX

MENU:	LEA DX, MENUT				;���˵�
		MOV AH, 09H
		INT 21H
		MOV AH, 01H
		INT 21H
		MOV AH, 09H
		LEA DX, CRLF
		INT 21H
		
		CMP AL, '1'
		JE FUNC1
		CMP AL, '2'
		JE FUNC2
		CMP AL, '3'
		JE FUNC3
		CMP AL, '4'
		JE FUNC4
		CMP AL, '8'
		JE FUNC8
		CMP AL, '9'
		JMP OVER
		JMP MENU
		
FUNC1:	LEA DX, INNAMET				;����1
		MOV AH, 09H
		INT 21H
		LEA DX, INNAME
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		LEA DI, INNAME+1
		MOV CL, [DI]
		CMP CL, 8
		JNE WRONG_NAME
		LEA DI, INNAME+2
		LEA SI, BNAME
CHECK_USER:							;���ֽڱȽ��û���
		MOV AL, [DI]
		CMP AL, [SI]
		JNE WRONG_NAME
		INC DI
		INC SI
		DEC CL
		JNZ CHECK_USER
		LEA DX, INPWDT
		MOV AH, 09H
		INT 21H
		LEA DX, INPWD
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		LEA DI, INPWD+1
		MOV CL, [DI]
		CMP CL, 6
		JNE WRONG_PWD
		LEA DI, INPWD+2
		LEA SI, BPASS
CHECK_PWD:							;���ֽڱȽ�����
		MOV AL, [DI]
		CMP AL, [SI]
		JNE WRONG_PWD
		INC DI
		INC SI
		DEC CL
		JNZ CHECK_PWD
		JMP LOGIN_S
WRONG_NAME:
		LEA DX, WRONGNAMET
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
WRONG_PWD:
		LEA DX, WRONGPWDT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
LOGIN_S:							;��½�ɹ�
		MOV AUTH, 1
		LEA DX, LOGINST
		MOV AH, 09H
		INT 21H
		MOV AH, 09H
		LEA DX, CRLF
		INT 21H
		JMP MENU
		
FUNC2:	LEA DX, INGOODT				;����2
		MOV AH, 09H
		INT 21H
		LEA DX, INGOOD
		MOV AH, 0AH
		INT 21H
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		MOV AX, -1
CHECK_GOOD:							;ѡ����һ���Ƚ���Ʒ
		INC AX
		CMP AX, 30
		JE WRONG_GOOD
		MOV CX, AX
		IMUL CX, 21
		ADD CX, OFFSET GA1
		MOV SI, CX
		LEA DI, INGOOD+1
		MOV CL, [DI]
		LEA DI, INGOOD+2
CHECK_NAME:							;�Ƚ���Ʒ��
		MOV BL, [DI]
		CMP BL, [SI]
		JNE CHECK_GOOD
		INC DI
		INC SI
		DEC CL
		JNZ CHECK_NAME
		MOV BL, [SI]
		CMP BL, 0
		JE CHANGE_GOOD
		JMP CHECK_GOOD
WRONG_GOOD:
		LEA DX, WRONGGOODT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
CHANGE_GOOD:						;����ѡ����Ʒ
		MOV CX, AX
		IMUL CX, 21
		ADD CX, OFFSET GA1
		MOV GOOD, CX
		LEA DX, CHANGEGOODT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
		
FUNC3:	MOV BX, GOOD				;����3
		CMP BX, 0
		JE NO_SELECTED
		MOV AX, 15[BX]
		MOV DX, 17[BX]
		CMP AX, DX
		JNE SELL_GOOD
		LEA DX, NOGOODT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
SELL_GOOD:
		INC DX
		MOV 17[BX], DX
		LEA DX, SELLGOODT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP FUNC4
NO_SELECTED:
		LEA DX, NOTSELEVTEDT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
		JMP MENU
		
FUNC4:	MOV BP, -1					;����4
		LEA DX, UPDATEPRIOT
		MOV AH, 09H
		INT 21H
		LEA DX, CRLF
		INT 21H
COMPUTE_PRIO:
		INC BP
		CMP BP, 30
		JE MENU
		LEA SI, GA1
		MOV CX, BP
		IMUL CX, 21
		ADD SI, CX
		MOV BX, SI
		ADD BX, 13
		MOV AX, [BX-2]
		MOV BX, [BX]
		MOVSX EAX, AX
		MOVSX EBX, BX
		MOV EDI, 128
		IMUL EDI
		IDIV EBX
		MOV ECX, EAX
		MOV BX, SI
		ADD BX, 15
		MOV AX, [BX+2]
		MOV BX, [BX]
		MOVSX EAX, AX
		MOVSX EBX, BX
		IMUL EDI
		MOV EDI, 2
		IDIV EDI
		MOV EDX, 0
		IDIV EBX
		ADD EAX, ECX
		MOV BX, SI
		ADD BX, 19
		MOV [BX], AX
		JMP COMPUTE_PRIO
		
FUNC8:	MOV BP, 4					;����8
		MOV BX, CS
GET_LETTER:
		MOV CL, 4;
		ROL BX, CL
		MOV DL, BL
		AND DL, 0FH
		CMP DL, 0AH
		JB IS_NUM
		ADD DL, 07H
IS_NUM:	ADD DL, 30H
		MOV AH, 02H
		INT 21H
		DEC BP
		JZ SHOW_OVER
		JMP GET_LETTER
SHOW_OVER:
		LEA DX, CRLF
		MOV AH, 09H
		INT 21H
		JMP MENU
		
OVER:	MOV AH, 4CH
		INT 21H
CODE 	ENDS
		END START