; mp2.asm
; Implement a stack calculator that can do the following operations:
; ADD, SUBTRACT, MULTIPLY, DIVIDE

; Inputs:
;   Console - postfix expression

; Outputs:
;   Console - [0 - F]{4}, evaluation of postfix expression
;   Register R5 - [0 - F]{4}, evaluation of postfix expression
; partners : yab2, rkadiri2, heshama2

.ORIG x3000
	
; PRINT_HEX
;   Description: prints out the value in R3 to the console
;   Inputs: R3 - value in register to be printed out
;   Outputs: Value printed to the console
PRINT_HEX

; INSERT CODE HERE!

	AND R0, R0, #0
	AND R6, R6, #0
	ADD R6, R6, #4		;CLEAR R6 AND START A 4 LOOP COUNTER
		

MAIN

; INSERT CODE HERE!
 
	BRnz DONE	
	AND R1,R1,#0
	AND R2,R2,#0
	ADD R1,R1,#4		;digit counter
	
CHECK
    BRnz BITCOUNTED
	ADD R2,R2,R2	;left shift digit 
	ADD R3,R3,#0	;add 0 if msb=0
	BRzp BIT	
	ADD R2,R2,#1	;add 1 to digit if msb=1
BIT
    ADD R3,R3,R3	;LEFT shift R3
	ADD R1,R1,#-1	;bit counter -1
	BRnzp CHECK	; if the 4-bit between 0 and 9 we shift to the value in ASCII
	; if it’s between 10 to 15, shift results in letters A to F
BITCOUNTED
    ADD R2,R2,#-9	; subtract 9 to see if it’s number or letter 
	BRnz GREATERNINE
	LD R4,ASCII_A	
	ADD R0,R2,R4
	BRnzp LESSERNINE
GREATERNINE
	LD R4,ASCII_9	
	ADD R0,R2,R4
LESSERNINE
    OUT		;output the ASCII number
	ADD R6,R6,#-1	;decrease main loop’s digit counter
	BRp MAIN

DONE	HALT

	

; EVALUATE
;   Description: handles input from console
;   Inputs: Console - input
;   Outputs: Console - evaluation of expression or error
;	     R5 - evalution of expression  
EVALUATE

; INSERT CODE HERE!
	GETC		;GET INPUT
	LD R4, N_SPACE 	; -32 WHICH IS NEGATIVE OF THE VALUE FOR ASCII SPACE
	ADD R4, R4, R0		;CHECKS FOR SPACE
	BRz	EVALUATE		;NEXT INPUT IF CHARACTER WAS A SPACE
	ADD R4, R4, #-16	; -32-16=-48 WHICH IS ASCII 0
	BRn OPERATOR		; INPUT LESS THAN 48 MEANS CHARACTER MAY BE AN OPERATOR
	ADD R4, R4, #-9		;VERIFIES IF CHARACTER IS A NUMBER BETWEEN ASCII 30 AND 39
	BRp EQUAL_SYM		; IF CHARACTER IS MORE THAN 39 IT MAY BE THE "=" SYMBOL
	OUT
	LD R5, N_ZERO		;IF IT IS A NUMBER SHIFT IT BY x30
	ADD R0, R0, R5
	JSR PUSH
	BRnzp EVALUATE

OPERATOR
	ADD R4, R4, #6
	BRn INVALID		;INVALID OPERATOR
	BRz MUL			; "*" MULTIPLICATION OPERATOR PRESENT
	ADD R4, R4, #-1
	BRz PLUS		; "+" PRESENT SO ADDITION
	ADD R4, R4, #-2
	BRz MIN			; "-" PRESENT SO SUBTRACTION
	ADD R4, R4, #-2
	BRz DIV			; "/" PRESENT SO DIVISION
	BRnzp INVALID

EQUAL_SYM
	ADD R6, R6, #-4
	BRz DONECALC
	BRnzp INVALID

INVALID 
	LEA R0, INVAL
	PUTS		;PRINTS THIS STRING WHEN INVALID INPUTS ARE RECEIVED
	HALT

UNDERFLO
	LEA R0, UNDER
	PUTS		;PRINTS THIS STRING WHEN UNDERFLOW IS PRESENT IN THE STACK
	HALT

DONECALC		;EXECUTED ONLY WHEN "=" IS DETECTED
	OUT
	JSR POP
	AND R3, R3, #0		;INITIALIZES R3 AND GETS RESULT
	ADD R3, R0, #0
	JSR POP
	ADD R5, R5, #0
	BRz UNDERFLO
	AND R5, R5, #0
	ADD R5, R3, #0		;INITIALIZES R5 AND STORES RESULT IN IT
	BRnzp PRINT_HEX



; PLUS
;   Description: adds two numbers (R0 = R3 + R4)
;   Inputs: R3 - addend
;	    R4 - addend
;   Outputs: R0 - sum
PLUS	

; INSERT CODE HERE!

	OUT
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R5, R5, #0
	BRnp INVALID		;CHECKING FOR UNDERFLOW
	ADD R3, R3, #0		
	JSR POP				;GETS NEXT VALUE
	ADD R5, R5, #0
	BRnp INVALID
	ADD R4, R4, R0
	ADD R0, R4, R3
	JSR PUSH
	BRnzp EVALUATE

	
; MIN
;   Description: subtracts two numbers (R0 = R3 - R4)
;   Inputs: R3 - minuend
;	    R4 - subtrahend
;   Outputs: R0 - difference
MIN	

; INSERT CODE HERE!

	OUT
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R5, R5, #0
	BRnp INVALID		;CHECKING FOR UNDERFLOW
	ADD R3, R3, #0	
	NOT R3, R3
	ADD R3, R3, #1		;CONVERTING VALUE IN R3 TO NEGATIVE	
	JSR POP				;GETS NEXT VALUE
	ADD R5, R5, #0
	BRnp INVALID
	ADD R4, R4, R0
	ADD R0, R4, R3
	JSR PUSH
	BRnzp EVALUATE


	
; MUL
;   Description: multiplies two numbers (R0 = R3 * R4)
;   Inputs: R3 - factor
;	    R4 - factor
;   Outputs: R0 - product
MUL	
	
; INSERT CODE HERE!

	OUT
	AND R3, R3, #0
	AND R4, R4, #0
	JSR POP
	ADD R5, R5, #0
	BRnp INVALID		;CHECKING FOR UNDERFLOW
	ADD R3, R0, #-1
	JSR POP
	ADD R5, R5, #0
	BRnp INVALID
	ADD R4, R4, R0
	ADD R3, R3, #0
	BRn MULOVER	; IF MULTIPLE IS 0 ANSWER IS ALWAYS 0
	BRz MULONE ; IF MULTIPLE IS 1 R4 WILL REMAIN THE SAME
	AND R6, R6, #0
	AND R0, R0, #0
MLOOP			;MULTIPLICATION LOOP
	ADD R6, R6, R4
	ADD R3, R3, #-1
	BRzp MLOOP
	ADD R0, R6, #0
	JSR PUSH
	BRnzp EVALUATE
MULONE			;NO CHANGE IF MULTIPLE IS 1
	ADD R4, R4, #0
	JSR PUSH
	BRnzp EVALUATE
MULOVER			;ANSWER IS 0 AS A MULTIPLE WAS 0
	AND R0, R0, #0
	JSR PUSH
	BRnzp EVALUATE


; DIV
;   Description: divides two numbers (R0 = R3 / R4)
;   Inputs: R3 - numerator
;	    R4 - denominator
;   Outputs: R0 - quotient
; INSERT CODE HERE!
DIV	
	OUT
	AND R4, R4, #0
	AND R3, R3, #0
	JSR POP
	ADD R4, R4, R0
	BRz INVALID		;division by 0 is invalid
	NOT R4, R4
	ADD R4, R4, #1
	ADD R5, R5, #0
	BRnp INVALID
	JSR POP
	ADD R5, R5, #0
	BRnp INVALID
	ADD R3, R3, R0
	AND R0, R0, #0
	
DIVLOOP 		;DIVISION LOOP
	ADD R0, R0, #1
	ADD R3, R3, R4
	BRp DIVLOOP
	ADD R1, R3, #0
	BRz DONEDIV
	LD R4, DENOMINATOR
	ADD R1, R1, R4
	ADD R0, R0, #-1
DONEDIV JSR PUSH
	BRnzp EVALUATE


	
; PUSH
;   Description: Pushes a charcter unto the stack
;   Inputs: R0 - character to push unto the stack
;   Outputs: R5 - 0 (success) or 1 (failure/overflow)
;   Registers: R3 - stores STACK_END
;	       R4 - stores STACK_TOP
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


; POP
;   Description: Pops a character off the stack
;   Inputs: 
;   Outputs: R0 - character popped off the stack
;	     R5 - 0 (success) or 1 (failure/underflow)
;   Registers: R3 - stores STACK_END
;	       R4 - stores STACK_TOP

POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
DENOMINATOR .BLKW #1
INVAL .STRINGZ "CHARACTER ENTERED OR OPERATION UNDEFINED!"
UNDER .STRINGZ "UNDERFLOW!"
N_SPACE .FILL #32
N_ZERO .FILL xFFD0	;-(ASCII0)
ASCII_A  .FILL #64		; ASCII ‘A’-1 
ASCII_9  .FILL #57		; ASCII ‘9’
.END
