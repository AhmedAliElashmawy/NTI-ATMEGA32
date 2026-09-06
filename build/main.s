	.file	"main.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.text.main,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
	sbi 55-32,0
	ldi r20,lo8(1)
	ldi r18,lo8(200)
	ldi r19,hi8(200)
.L3:
	in r24,56-32
	eor r24,r20
	out 56-32,r24
	ldi r24,lo8(5000)
	ldi r25,hi8(5000)
.L2:
	movw r30,r18
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r30,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	sbiw r24,1
	brne .L2
	rjmp .L3
	.size	main, .-main
