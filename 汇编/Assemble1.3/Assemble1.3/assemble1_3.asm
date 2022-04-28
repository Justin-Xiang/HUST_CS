.686P
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 scanf    PROTO C : dword,:vararg;
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
.DATA
    npFmt   db  "%c",0
	NFmt    db  "%s",0
    lpFmt	db	"%s",0ah, 0dh, 0
	numFmt  db  "%d",0
	GFmt    db  "进货价:%d,销售价:%d,进货数量:%d,已售数量;%d,利润率:%d%%",0ah,0dh,0
	choose  db  0
	BNAME  	DB  'LIAOXIANG',0
	NAME_LEN  DW $-BNAME
	BPASS   DB  'U201915116',0
	PASS_LEN  DW $-BPASS
	NAME_A 	DB  'TIANTIAN',0
	AUTH	DB  0
	GOODIN  DD  0
	GOODOUT DD  0
	GOODINN DD  0
	GOODOUTN  DD  0
	GOODRATE  DD  0
	GOOD	DD  'Q',0
	N       	EQU  30
	SNAME	DB  'SHOP',0
	GA1   DB   'PEN', 7 DUP(0)  
      DD   15,20,70,25,?
    GA2   DB  'PENCIL', 4 DUP(0) ;商品2 名称
      DD   2,3,100,50,?
    GA3   DB   'BOOK', 6 DUP(0) ;商品3 名称
      DD   30,40,25,5,?
    GA4   DB   'RULER',5 DUP(0)  ;商品4 名称
      DD   3,4,200,150,?
    GAN   DB N-4 DUP('TempValue',0,15,0,0,0,20,0,0,0,30,0,0,0,2,0,0,0,?,?,?,?) 
	CLEAR  db 0
	IN_NAME		DB  '00000000000',0
	IN_PWD		DB  '00000000000',0
	IN_GOOD	DB  11
			DB  ?
			DB  11 DUP(0),0
	IN_NUM  DD  0
	OUT_NUM DD  0
	HP		DB  'HP : ',0
	GOODNOW	DB  'Good now : ',0
	MEUM	DB  '1. 查找物品信息',0AH
			DB  '2. 出货',0AH
			DB  '3. 进货',0AH
			;DB  '3. Place an order',0AH
			DB  '4. 计算利润率',0AH
			DB  '5. 略',0AH
			DB  '6. 略',0AH
			DB  '7. 略',0AH
			DB  '8. 略',0AH
			DB  '9. Exit',0AH
			DB  'Input your choice(1~9) :',0
	PROMPTHP	DB  'Input the name :',0
	ERROR		DB  'The name/pass is wrong!',0
	PROMPTPWD	DB  'Input the pass :',0
	PROMPTGOOD	DB  'Input the good :',0
	PROMPTINNUM	DB  '输入进货量 :',0
	PROMPTOUTNUM	DB  '输入出货量 :',0
	NUMERROR    DB  '出货量过多，请查询后重新输入',0
	ZEROERROR   DB  '请输入大于0的整数',0
	ERRORGOOD	DB  'Not Exist!',0
	ERRORBUY	DB  'Nothing!',0
	SUCCESS		DB  'Success!',0
	CRLF		DB  0DH,0AH		;注意要加$结尾
.STACK  200
.CODE
main proc c
T1:	
	invoke printf,offset lpFmt,OFFSET PROMPTHP
	invoke scanf,offset NFmt,offset IN_NAME
	invoke printf,offset lpFmt,OFFSET CRLF
	LEA  ESI, BNAME		;比较用户名
	LEA  EDI, IN_NAME
	MOV  CX, NAME_LEN
	LOPA1:	MOV  AL, [ESI]
		MOV  BL, [EDI]
		CMP  AL, BL
		JNE  ERROR1	;输入不正确，跳转
		INC  ESI
		INC  EDI
		DEC  CX
		JNE  LOPA1	;CX不等于0，跳转

	invoke printf,offset lpFmt,OFFSET PROMPTPWD
	invoke scanf,offset NFmt,offset IN_PWD
	invoke printf,offset lpFmt,OFFSET CRLF

	LEA  ESI, BPASS		;比较密码
	LEA  EDI, IN_PWD
	MOV  CX, PASS_LEN
	LOPA2:	MOV  AL, [ESI]
		MOV  BL, [EDI]
		CMP  AL, BL
		JNE  ERROR1	;输入不正确，跳转
		INC  ESI
		INC  EDI
		DEC  CX
		JNE  LOPA2	;CX不等于0，跳转
		MOV  AUTH, 1
		JMP  C0
	ERROR1:	invoke printf,offset lpFmt,OFFSET ERROR
		invoke printf,offset lpFmt,OFFSET CRLF
		JMP  T1
C0:	;invoke printf,offset lpFmt,OFFSET HP
    ;invoke printf,offset lpFmt,OFFSET CRLF
	;invoke printf,offset lpFmt,OFFSET GOODNOW
	LEA  ESI, GOOD
	MOV  ESI, [ESI]		
	CMP ESI, 'Q'
	JNE OUTGOOD
	JE OUTMENU
OUTGOOD:
	invoke printf,offset lpFmt,OFFSET GOOD
	invoke printf,offset lpFmt,OFFSET CRLF
OUTMENU:
	invoke printf,offset lpFmt,OFFSET MEUM
	;invoke printf,offset lpFmt,OFFSET CRLF
	SC:invoke scanf,offset npFmt,offset choose
	;invoke printf,offset lpFmt,OFFSET CRLF
	CMP  choose, '1'
	JE  C1
	CMP  choose, '2'
	JE  C2
	CMP  choose, '3'
	JE  C3
	CMP  choose, '4'
	JE  C4
	CMP  choose, '5'
	JE  C5
	CMP  choose, '6'
	JE  C6
	CMP  choose, '7'
	JE  C7
	CMP  choose, '8'
	JE  C8
	CMP  choose, '9'
	JE  C9
	JNE SC
	invoke printf,offset lpFmt,OFFSET CRLF
	
C1:	
	invoke printf,offset lpFmt,OFFSET PROMPTGOOD
	MOV  EAX,0
	MOV  EDI,OFFSET IN_GOOD
	MOV  ECX,0
	CLR:
	    MOV  [EDI],EAX
		ADD  EDI,4
		ADD  ECX,4
		CMP  ECX,12
		JNZ  CLR
	invoke scanf,offset NFmt,offset IN_GOOD

	MOV  BX, 30
	LEA  ESI, GA1		;比较商品名
	LEA  EDI, IN_GOOD
	LBX:	MOV  CX, 10
	LCX:	MOV  AL, [ESI]
		MOV  AH, [EDI]
		CMP  AL, AH
		JNE  NEXTG	;输入不正确，跳转
		INC  ESI
		INC  EDI
		DEC  CX
		JNE  LCX		;CX不等于0，跳转
		SUB  ESI, 10
		MOV  EAX,[ESI+10]
		MOV  GOODIN,EAX
		MOV  EAX,[ESI+14]
		MOV  GOODOUT,EAX
		MOV  EAX,[ESI+18]
		MOV  GOODINN,EAX
		MOV  EAX,[ESI+22]
		MOV  GOODOUTN,EAX
		MOV  EAX,[ESI+26]
		MOV  GOODRATE,EAX
		invoke printf,offset GFmt,GOODIN,GOODOUT,GOODINN,GOODOUTN,GOODRATE
		JMP  OUTMENU
	NEXTG:	ADD SI, CX
		ADD SI, 20	;偏移地址改变用加，不能MOV SI,[SI+BP+11]
		LEA DI, IN_GOOD
		DEC BX;
		CMP  BX, 0
		JE  ERROR2
		JNE  LBX
	ERROR2:	
	    invoke printf,offset lpFmt,OFFSET ERRORGOOD
		JMP  OUTMENU
C2:
    invoke printf,offset lpFmt,OFFSET PROMPTGOOD
	invoke scanf,offset NFmt,offset IN_GOOD

	MOV  BX, 30
	LEA  ESI, GA1		;比较商品名
	LEA  EDI, IN_GOOD
	LBX_2:	MOV  CX, 10
	LCX_2:	MOV  AL, [ESI]
		MOV  AH, [EDI]
		CMP  AL, AH
		JNE  NEXTG_2	;输入不正确，跳转
		INC  ESI
		INC  EDI
		DEC  CX
		JNE  LCX_2		;CX不等于0，跳转
		SUB  ESI, 10
		MOV  EAX,[ESI+10]
		MOV  GOODIN,EAX
		MOV  EAX,[ESI+14]
		MOV  GOODOUT,EAX
		MOV  EAX,[ESI+18]
		MOV  GOODINN,EAX
		MOV  EAX,[ESI+22]
		MOV  GOODOUTN,EAX
		MOV  EAX,[ESI+26]
		MOV  GOODRATE,EAX
	OUTNUM:
		invoke printf,offset lpFmt,OFFSET PROMPTOUTNUM
	    invoke scanf,offset numFmt,offset OUT_NUM
		MOV  EBX,OUT_NUM
		MOV  EAX,GOODINN
		SUB  EAX,GOODOUTN
		CMP  EAX,EBX
		JAE  PR_2
		JMP  OUT_ERROR_2
	NEXTG_2:	ADD SI, CX
		ADD SI, 20	;偏移地址改变用加，不能MOV SI,[SI+BP+11]
		LEA DI, IN_GOOD
		DEC BX;
		CMP  BX, 0
		JE  ERROR_2
		JNE  LBX_2
	PR_2:
	    MOV  EAX,GOODOUTN
		ADD  EAX,EBX
		MOV  [ESI+22],EAX
		MOV  GOODOUTN,EAX
	    invoke printf,offset GFmt,GOODIN,GOODOUT,GOODINN,GOODOUTN,GOODRATE
		JMP  OUTMENU
	ERROR_2:	
	    invoke printf,offset lpFmt,OFFSET ERRORGOOD
		JMP  C2
	OUT_ERROR_2:
	    invoke printf,offset lpFmt,OFFSET NUMERROR
		JMP  OUTNUM

C3:
    invoke printf,offset lpFmt,OFFSET PROMPTGOOD
	invoke scanf,offset NFmt,offset IN_GOOD

	MOV  BX, 30
	LEA  ESI, GA1		;比较商品名
	LEA  EDI, IN_GOOD
	LBX_3:	MOV  CX, 10
	LCX_3:	MOV  AL, [ESI]
		MOV  AH, [EDI]
		CMP  AL, AH
		JNE  NEXTG_3	;输入不正确，跳转
		INC  ESI
		INC  EDI
		DEC  CX
		JNE  LCX_3		;CX不等于0，跳转
		SUB  ESI, 10
		MOV  EAX,[ESI+10]
		MOV  GOODIN,EAX
		MOV  EAX,[ESI+14]
		MOV  GOODOUT,EAX
		MOV  EAX,[ESI+18]
		MOV  GOODINN,EAX
		MOV  EAX,[ESI+22]
		MOV  GOODOUTN,EAX
		MOV  EAX,[ESI+26]
		MOV  GOODRATE,EAX
	INNUM:
		invoke printf,offset lpFmt,OFFSET PROMPTINNUM
	    invoke scanf,offset numFmt,offset IN_NUM
		MOV  EBX,IN_NUM
		CMP  EBX,0
		JAE  PR_3
		JMP  OUT_ERROR_3
	NEXTG_3:	ADD SI, CX
		ADD SI, 20	;偏移地址改变用加，不能MOV SI,[SI+BP+11]
		LEA DI, IN_GOOD
		DEC BX;
		CMP  BX, 0
		JE  ERROR_3
		JNE  LBX_3
	PR_3:
	    MOV  EAX,GOODINN
		ADD  EAX,EBX
		MOV  [ESI+18],EAX
		MOV  GOODINN,EAX
	    invoke printf,offset GFmt,GOODIN,GOODOUT,GOODINN,GOODOUTN,GOODRATE
		JMP  OUTMENU
	ERROR_3:	
	    invoke printf,offset lpFmt,OFFSET ERRORGOOD
		JMP  C2
	OUT_ERROR_3:
	    invoke printf,offset lpFmt,OFFSET ZEROERROR
		JMP  INNUM


C4:	
    MOV  BX, 30
	LEA  ESI, GA1		;比较商品名
	LBX_4:
	MOV  EAX,[ESI+10]
	MOV  GOODIN,EAX
	MOV  EAX,[ESI+14]
	MOV  GOODOUT,EAX
	MOV  EAX,[ESI+18]
	MOV  GOODINN,EAX
	MOV  EAX,[ESI+22]
	MOV  GOODOUTN,EAX
	MOV  EAX,[ESI+26]
	MOV  GOODRATE,EAX
	MOV  EDX,[ESI+10]
	MOV  EAX,[ESI+14]
	IMUL EAX,GOODOUTN
	IMUL EDX,GOODINN
	SUB  EAX,EDX
	CMP  EAX,0
	JL   BB
	IMUL EAX,100
	MOV  ECX,EDX
	MOV  EDX,0
	IDIV ECX
	MOV [ESI+26],EAX
	ADD SI, 30	
	DEC BX
	CMP  BX, 0
	JE  OUTMENU
	JNE  LBX_4
    BB:
	NEG  EAX
	IMUL EAX,100
	MOV  ECX,EDX
	MOV  EDX,0
	IDIV ECX
	NEG  EAX
	MOV [ESI+26],EAX
	ADD SI, 30	
	DEC BX
	CMP  BX, 0
	JE  OUTMENU
	JNE  LBX_4

C5:	JMP  C0
C6:	JMP  C0
C7:	JMP  C0
C8:	JMP C0
C9:	
	invoke ExitProcess,0
main endp
END