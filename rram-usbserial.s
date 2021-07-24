	.file	"rram-usbserial.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.RingBuffer_Insert,"ax",@progbits
	.type	RingBuffer_Insert, @function
RingBuffer_Insert:
.LFB104:
	.file 1 "Lib/RingBuffer.h"
	.loc 1 77 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 78 0
	movw r30,r24
	subi r30,-128
	sbci r31,-1
	ld r26,Z
	ldd r27,Z+1
	st X,r22
	.loc 1 80 0
	ld r26,Z
	ldd r27,Z+1
	movw r18,r26
	subi r18,-1
	sbci r19,-1
	std Z+1,r19
	st Z,r18
	cp r18,r30
	cpc r19,r31
	brne .L2
	.loc 1 81 0
	adiw r26,1+1
	st X,r25
	st -X,r24
	sbiw r26,1
.L2:
.LBB92:
	.loc 1 83 0
	in r18,__SREG__
.LVL1:
.LBB93:
.LBB94:
	.file 2 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h"
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL2:
/* #NOAPP */
.LBE94:
.LBE93:
	.loc 1 85 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r24,Z
	ldd r25,Z+1
.LVL3:
	adiw r24,1
	std Z+1,r25
	st Z,r24
.LVL4:
.LBB95:
.LBB96:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL5:
	ret
.LBE96:
.LBE95:
.LBE92:
	.cfi_endproc
.LFE104:
	.size	RingBuffer_Insert, .-RingBuffer_Insert
	.section	.text.RingBuffer_Remove,"ax",@progbits
	.type	RingBuffer_Remove, @function
RingBuffer_Remove:
.LFB105:
	.loc 1 101 0
	.cfi_startproc
.LVL6:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 102 0
	movw r26,r24
	subi r26,126
	sbci r27,-1
	ld r30,X+
	ld r31,X
	sbiw r26,1
	ld r20,Z+
.LVL7:
	.loc 1 104 0
	adiw r26,1
	st X,r31
	st -X,r30
	movw r18,r24
	subi r18,-128
	sbci r19,-1
	cp r30,r18
	cpc r31,r19
	brne .L5
	.loc 1 105 0
	st X+,r24
	st X,r25
.L5:
.LBB97:
	.loc 1 107 0
	in r21,__SREG__
.LVL8:
.LBB98:
.LBB99:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL9:
/* #NOAPP */
.LBE99:
.LBE98:
	.loc 1 109 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r18,Z
	ldd r19,Z+1
	subi r18,1
	sbc r19,__zero_reg__
	std Z+1,r19
	st Z,r18
.LVL10:
.LBB100:
.LBB101:
	.loc 2 70 0
	out __SREG__,r21
	.loc 2 71 0
.LVL11:
.LBE101:
.LBE100:
.LBE97:
	.loc 1 113 0
	mov r24,r20
.LVL12:
	ret
	.cfi_endproc
.LFE105:
	.size	RingBuffer_Remove, .-RingBuffer_Remove
	.section	.text.SW_PulseClock,"ax",@progbits
	.type	SW_PulseClock, @function
SW_PulseClock:
.LFB118:
	.file 3 "Lib/SWD.h"
	.loc 3 157 0
	.cfi_startproc
.LVL13:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LBB102:
	.loc 3 158 0
	ldi r25,0
.LVL14:
.L7:
	.loc 3 158 0 is_stmt 0 discriminator 1
	cp r25,r24
	breq .L9
	.loc 3 159 0 is_stmt 1 discriminator 3
	in r18,0x8
	subi r18,lo8(-(-128))
	out 0x8,r18
	.loc 3 160 0 discriminator 3
	in r18,0x8
	subi r18,lo8(-(-128))
	out 0x8,r18
	.loc 3 158 0 discriminator 3
	subi r25,lo8(-(1))
.LVL15:
	rjmp .L7
.L9:
/* epilogue start */
.LBE102:
	.loc 3 162 0
	ret
	.cfi_endproc
.LFE118:
	.size	SW_PulseClock, .-SW_PulseClock
	.section	.text.SW_Send,"ax",@progbits
	.type	SW_Send, @function
SW_Send:
.LFB120:
	.loc 3 179 0
	.cfi_startproc
.LVL16:
	push r12
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 12, -2
	push r13
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 13, -3
	push r14
.LCFI2:
	.cfi_def_cfa_offset 5
	.cfi_offset 14, -4
	push r15
.LCFI3:
	.cfi_def_cfa_offset 6
	.cfi_offset 15, -5
	push r16
.LCFI4:
	.cfi_def_cfa_offset 7
	.cfi_offset 16, -6
	push r17
.LCFI5:
	.cfi_def_cfa_offset 8
	.cfi_offset 17, -7
	push r28
.LCFI6:
	.cfi_def_cfa_offset 9
	.cfi_offset 28, -8
	push r29
.LCFI7:
	.cfi_def_cfa_offset 10
	.cfi_offset 29, -9
/* prologue: function */
/* frame size = 0 */
/* stack size = 8 */
.L__stack_usage = 8
	movw r12,r22
	movw r14,r24
.LVL17:
	mov r16,r20
	ldi r17,0
.LBB103:
	.loc 3 181 0
	ldi r28,0
	ldi r29,0
.LVL18:
.L11:
	.loc 3 181 0 is_stmt 0 discriminator 1
	cp r28,r16
	cpc r29,r17
	breq .L15
	.loc 3 183 0 is_stmt 1
	movw r26,r14
	movw r24,r12
	mov r0,r28
	rjmp 2f
	1:
	lsr r27
	ror r26
	ror r25
	ror r24
	2:
	dec r0
	brpl 1b
	sbrs r24,0
	rjmp .L12
	.loc 3 184 0
	sbi 0x8,6
	rjmp .L13
.L12:
	.loc 3 186 0
	cbi 0x8,6
.L13:
	.loc 3 189 0 discriminator 2
	ldi r24,lo8(1)
	call SW_PulseClock
.LVL19:
	adiw r28,1
.LVL20:
	rjmp .L11
.L15:
/* epilogue start */
.LBE103:
	.loc 3 191 0
	pop r29
	pop r28
.LVL21:
	pop r17
	pop r16
.LVL22:
	pop r15
	pop r14
	pop r13
	pop r12
.LVL23:
	ret
	.cfi_endproc
.LFE120:
	.size	SW_Send, .-SW_Send
	.section	.text.I2C_StartTransmission,"ax",@progbits
	.type	I2C_StartTransmission, @function
I2C_StartTransmission:
.LFB133:
	.file 4 "Board/../Lib/I2C.h"
	.loc 4 31 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 4 32 0
	sbi 0xa,1
	.loc 4 33 0
	sbi 0xa,0
	.loc 4 35 0
	sbi 0xb,1
	.loc 4 36 0
	sbi 0xb,0
	.loc 4 37 0
	cbi 0xb,1
	.loc 4 38 0
	cbi 0xb,0
	ret
	.cfi_endproc
.LFE133:
	.size	I2C_StartTransmission, .-I2C_StartTransmission
	.section	.text.I2C_EndTransmission,"ax",@progbits
	.type	I2C_EndTransmission, @function
I2C_EndTransmission:
.LFB134:
	.loc 4 45 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 4 46 0
	cbi 0xb,1
	.loc 4 47 0
	sbi 0xb,0
	.loc 4 48 0
	sbi 0xb,1
	.loc 4 50 0
	cbi 0xa,1
	.loc 4 51 0
	cbi 0xa,0
	ret
	.cfi_endproc
.LFE134:
	.size	I2C_EndTransmission, .-I2C_EndTransmission
	.section	.text.I2C_SendByte,"ax",@progbits
	.type	I2C_SendByte, @function
I2C_SendByte:
.LFB135:
	.loc 4 58 0
	.cfi_startproc
.LVL24:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 4 58 0
	ldi r18,lo8(7)
	ldi r19,0
.LBB104:
	.loc 4 62 0
	ldi r25,0
.LVL25:
.L21:
	movw r20,r24
	mov r0,r18
	rjmp 2f
	1:
	asr r21
	ror r20
	2:
	dec r0
	brpl 1b
	sbrs r20,0
	rjmp .L19
	.loc 4 63 0
	sbi 0xb,1
	rjmp .L20
.L19:
	.loc 4 65 0
	cbi 0xb,1
.L20:
	.loc 4 68 0 discriminator 2
	sbi 0xb,0
	.loc 4 69 0 discriminator 2
	cbi 0xb,0
.LVL26:
.LVL27:
	subi r18,1
	sbc r19,__zero_reg__
	brcc .L21
.LBE104:
	.loc 4 74 0
	sbi 0xb,1
	.loc 4 75 0
	cbi 0xa,1
	.loc 4 76 0
	sbi 0xb,0
	.loc 4 77 0
	in r24,0x9
.LVL28:
	.loc 4 78 0
	cbi 0xb,0
	.loc 4 79 0
	sbi 0xa,1
	.loc 4 82 0
	lsr r24
	andi r24,1
.LVL29:
	ret
	.cfi_endproc
.LFE135:
	.size	I2C_SendByte, .-I2C_SendByte
	.section	.text.PM_UpdateReg,"ax",@progbits
	.type	PM_UpdateReg, @function
PM_UpdateReg:
.LFB139:
	.file 5 "Board/PM.h"
	.loc 5 95 0
	.cfi_startproc
.LVL30:
	push r16
.LCFI8:
	.cfi_def_cfa_offset 3
	.cfi_offset 16, -2
	push r17
.LCFI9:
	.cfi_def_cfa_offset 4
	.cfi_offset 17, -3
	push r28
.LCFI10:
	.cfi_def_cfa_offset 5
	.cfi_offset 28, -4
	push r29
.LCFI11:
	.cfi_def_cfa_offset 6
	.cfi_offset 29, -5
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
	mov r17,r24
	mov r16,r22
	mov r29,r20
.LVL31:
.LBB112:
.LBB113:
	.loc 5 81 0
	call I2C_StartTransmission
.LVL32:
	.loc 5 82 0
	ldi r24,lo8(120)
	call I2C_SendByte
.LVL33:
	.loc 5 83 0
	mov r24,r17
	call I2C_SendByte
.LVL34:
	.loc 5 84 0
	call I2C_StartTransmission
.LVL35:
	.loc 5 85 0
	ldi r24,lo8(121)
	call I2C_SendByte
.LVL36:
.LBB114:
.LBB115:
	.loc 4 92 0
	sbi 0xb,1
	.loc 4 93 0
	cbi 0xa,1
.LVL37:
	ldi r18,lo8(7)
	ldi r19,0
	.loc 4 89 0
	ldi r28,0
.LBB116:
	.loc 4 98 0
	ldi r20,lo8(1)
	ldi r21,0
.LVL38:
.L25:
	.loc 4 97 0
	sbi 0xb,0
	.loc 4 98 0
	sbis 0x9,1
	rjmp .L26
	movw r24,r20
	mov r0,r18
	rjmp 2f
	1:
	lsl r24
	2:
	dec r0
	brpl 1b
	rjmp .L24
.L26:
	ldi r24,0
	ldi r25,0
.L24:
	or r28,r24
.LVL39:
	.loc 4 99 0
	cbi 0xb,0
.LVL40:
.LVL41:
	subi r18,1
	sbc r19,__zero_reg__
	brcc .L25
.LBE116:
	.loc 4 103 0
	cbi 0xb,1
	.loc 4 104 0
	sbi 0xa,1
	.loc 4 105 0
	sbi 0xb,0
	.loc 4 106 0
	cbi 0xb,0
	.loc 4 107 0
	sbi 0xb,1
.LVL42:
.LBE115:
.LBE114:
	.loc 5 87 0
	call I2C_EndTransmission
.LVL43:
.LBE113:
.LBE112:
.LBB117:
.LBB118:
	.loc 5 68 0
	call I2C_StartTransmission
.LVL44:
	.loc 5 69 0
	ldi r24,lo8(120)
	call I2C_SendByte
.LVL45:
	.loc 5 70 0
	mov r24,r17
	call I2C_SendByte
.LVL46:
	.loc 5 71 0
	mov r24,r29
	com r24
	and r24,r28
	or r24,r16
.LVL47:
	call I2C_SendByte
.LVL48:
/* epilogue start */
.LBE118:
.LBE117:
	.loc 5 97 0
	pop r29
.LVL49:
	pop r28
.LVL50:
	pop r17
.LVL51:
	pop r16
.LVL52:
.LBB120:
.LBB119:
	.loc 5 72 0
	jmp I2C_EndTransmission
.LVL53:
.LBE119:
.LBE120:
	.cfi_endproc
.LFE139:
	.size	PM_UpdateReg, .-PM_UpdateReg
	.section	.text.getParity,"ax",@progbits
.global	getParity
	.type	getParity, @function
getParity:
.LFB115:
	.loc 3 120 0
	.cfi_startproc
.LVL54:
	push r12
.LCFI12:
	.cfi_def_cfa_offset 3
	.cfi_offset 12, -2
	push r13
.LCFI13:
	.cfi_def_cfa_offset 4
	.cfi_offset 13, -3
	push r14
.LCFI14:
	.cfi_def_cfa_offset 5
	.cfi_offset 14, -4
	push r15
.LCFI15:
	.cfi_def_cfa_offset 6
	.cfi_offset 15, -5
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
.LVL55:
	.loc 3 121 0
	ldi r18,0
	.loc 3 123 0
	ldi r19,lo8(1)
.LVL56:
.L29:
	.loc 3 122 0
	cp r22,__zero_reg__
	cpc r23,__zero_reg__
	cpc r24,__zero_reg__
	cpc r25,__zero_reg__
	breq .L31
	.loc 3 123 0
	eor r18,r19
.LVL57:
	.loc 3 124 0
	movw r12,r22
	movw r14,r24
	ldi r20,1
	sub r12,r20
	sbc r13,__zero_reg__
	sbc r14,__zero_reg__
	sbc r15,__zero_reg__
	and r22,r12
	and r23,r13
	and r24,r14
	and r25,r15
.LVL58:
	rjmp .L29
.L31:
	.loc 3 127 0
	mov r24,r18
/* epilogue start */
	pop r15
	pop r14
	pop r13
	pop r12
	ret
	.cfi_endproc
.LFE115:
	.size	getParity, .-getParity
	.section	.text.__vector_9,"ax",@progbits
.global	__vector_9
	.type	__vector_9, @function
__vector_9:
.LFB163:
	.loc 5 214 0
	.cfi_startproc
	push r1
.LCFI16:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI17:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
/* epilogue start */
	.loc 5 215 0
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE163:
	.size	__vector_9, .-__vector_9
	.section	.text.__vector_10,"ax",@progbits
.global	__vector_10
	.type	__vector_10, @function
__vector_10:
.LFB164:
	.loc 5 217 0
	.cfi_startproc
	push r1
.LCFI18:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI19:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI20:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI21:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI22:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI23:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI24:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r23
.LCFI25:
	.cfi_def_cfa_offset 10
	.cfi_offset 23, -9
	push r24
.LCFI26:
	.cfi_def_cfa_offset 11
	.cfi_offset 24, -10
	push r25
.LCFI27:
	.cfi_def_cfa_offset 12
	.cfi_offset 25, -11
	push r26
.LCFI28:
	.cfi_def_cfa_offset 13
	.cfi_offset 26, -12
	push r27
.LCFI29:
	.cfi_def_cfa_offset 14
	.cfi_offset 27, -13
	push r30
.LCFI30:
	.cfi_def_cfa_offset 15
	.cfi_offset 30, -14
	push r31
.LCFI31:
	.cfi_def_cfa_offset 16
	.cfi_offset 31, -15
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	.loc 5 218 0
	sbis 0x6,2
	rjmp .L34
.LVL59:
.LBB165:
.LBB166:
.LBB167:
	.loc 5 110 0
	ldi r20,lo8(31)
	ldi r22,lo8(19)
	ldi r24,lo8(10)
	call PM_UpdateReg
.LVL60:
.LBE167:
.LBE166:
.LBB168:
.LBB169:
	.loc 5 112 0
	ldi r20,lo8(31)
	ldi r22,lo8(24)
	ldi r24,lo8(14)
	call PM_UpdateReg
.LVL61:
.LBE169:
.LBE168:
.LBB170:
.LBB171:
	.loc 5 111 0
	ldi r20,lo8(31)
	ldi r22,lo8(29)
	ldi r24,lo8(12)
	call PM_UpdateReg
.LVL62:
.LBE171:
.LBE170:
.LBB172:
.LBB173:
	.loc 5 113 0
	ldi r20,lo8(31)
	ldi r22,lo8(11)
	ldi r24,lo8(16)
	call PM_UpdateReg
.LVL63:
.LBE173:
.LBE172:
.LBB174:
.LBB175:
	.loc 5 122 0
	ldi r20,lo8(4)
	ldi r22,lo8(4)
	ldi r24,lo8(5)
	call PM_UpdateReg
.LVL64:
.LBE175:
.LBE174:
.LBB176:
.LBB177:
	.loc 5 123 0
	ldi r20,lo8(4)
	ldi r22,lo8(4)
	ldi r24,lo8(6)
	call PM_UpdateReg
.LVL65:
.LBE177:
.LBE176:
.LBB178:
.LBB179:
	.loc 5 121 0
	ldi r20,lo8(-128)
	ldi r22,lo8(-128)
	ldi r24,lo8(4)
	call PM_UpdateReg
.LVL66:
.LBE179:
.LBE178:
.LBB180:
.LBB181:
	.loc 5 118 0
	ldi r20,lo8(-128)
	ldi r22,lo8(-128)
	ldi r24,lo8(1)
	call PM_UpdateReg
.LVL67:
.LBE181:
.LBE180:
.LBB182:
.LBB183:
	.loc 5 119 0
	ldi r20,lo8(-128)
	ldi r22,lo8(-128)
	ldi r24,lo8(2)
	call PM_UpdateReg
.LVL68:
.LBE183:
.LBE182:
.LBB184:
.LBB185:
	.loc 5 120 0
	ldi r20,lo8(-128)
	ldi r22,lo8(-128)
	ldi r24,lo8(3)
	rjmp .L36
.L34:
.LBE185:
.LBE184:
.LBE165:
	.loc 5 220 0
	sbic 0x6,2
	rjmp .L33
.LBB186:
.LBB187:
.LBB188:
	.loc 5 128 0
	ldi r20,lo8(-128)
	ldi r22,0
	ldi r24,lo8(1)
	call PM_UpdateReg
.LVL69:
.LBE188:
.LBE187:
.LBB189:
.LBB190:
	.loc 5 129 0
	ldi r20,lo8(-128)
	ldi r22,0
	ldi r24,lo8(2)
	call PM_UpdateReg
.LVL70:
.LBE190:
.LBE189:
.LBB191:
.LBB192:
	.loc 5 130 0
	ldi r20,lo8(-128)
	ldi r22,0
	ldi r24,lo8(3)
	call PM_UpdateReg
.LVL71:
.LBE192:
.LBE191:
.LBB193:
.LBB194:
	.loc 5 132 0
	ldi r20,lo8(4)
	ldi r22,0
	ldi r24,lo8(5)
	call PM_UpdateReg
.LVL72:
.LBE194:
.LBE193:
.LBB195:
.LBB196:
	.loc 5 133 0
	ldi r20,lo8(4)
	ldi r22,0
	ldi r24,lo8(6)
	call PM_UpdateReg
.LVL73:
.LBE196:
.LBE195:
.LBB197:
.LBB198:
	.loc 5 131 0
	ldi r20,lo8(-128)
	ldi r22,0
	ldi r24,lo8(4)
.L36:
	call PM_UpdateReg
.LVL74:
.L33:
/* epilogue start */
.LBE198:
.LBE197:
.LBE186:
	.loc 5 222 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE164:
	.size	__vector_10, .-__vector_10
	.section	.text.SetupHardware,"ax",@progbits
.global	SetupHardware
	.type	SetupHardware, @function
SetupHardware:
.LFB170:
	.file 6 "rram-usbserial.c"
	.loc 6 98 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 6 100 0
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
.LBB243:
.LBB244:
	.file 7 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/avr/wdt.h"
	.loc 7 515 0
/* #APP */
 ;  515 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/avr/wdt.h" 1
	in __tmp_reg__,__SREG__
	cli
	wdr
	lds r24,96
	ori r24,24
	sts 96,r24
	sts 96,__zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
/* #NOAPP */
.LBE244:
.LBE243:
	.loc 6 104 0
	ldi r24,lo8(-112)
	sts 97,r24
.LVL75:
.LBB245:
.LBB246:
	.loc 1 32 0
	in r18,__SREG__
.LVL76:
.LBB247:
.LBB248:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL77:
/* #NOAPP */
.LBE248:
.LBE247:
	.loc 1 34 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	sts USBtoUSART_Buffer+128+1,r25
	sts USBtoUSART_Buffer+128,r24
	.loc 1 35 0
	sts USBtoUSART_Buffer+130+1,r25
	sts USBtoUSART_Buffer+130,r24
.LVL78:
.LBB249:
.LBB250:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL79:
.LBE250:
.LBE249:
.LBE246:
.LBE245:
.LBB251:
.LBB252:
	.loc 1 32 0
	in r18,__SREG__
.LVL80:
.LBB253:
.LBB254:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL81:
/* #NOAPP */
.LBE254:
.LBE253:
	.loc 1 34 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
	.loc 1 35 0
	sts USARTtoUSB_Buffer+130+1,r25
	sts USARTtoUSB_Buffer+130,r24
.LVL82:
.LBB255:
.LBB256:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL83:
.LBE256:
.LBE255:
.LBE252:
.LBE251:
	.loc 6 111 0
/* #APP */
 ;  111 "rram-usbserial.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB257:
.LBB258:
	.file 8 "./Board/Dataflash.h"
	.loc 8 41 0
	sbi 0x5,4
	.loc 8 42 0
	sbi 0x4,4
.LBE258:
.LBE257:
.LBB259:
.LBB260:
	.file 9 "Board/DAC.h"
	.loc 9 60 0
	sbi 0x5,5
	.loc 9 61 0
	sbi 0x4,5
	.loc 9 63 0
	sbi 0x5,6
	.loc 9 64 0
	sbi 0x4,6
.LBE260:
.LBE259:
.LBB261:
.LBB262:
	.file 10 "Board/RRAM.h"
	.loc 10 34 0
	sbi 0xb,7
	.loc 10 35 0
	sbi 0xa,7
	.loc 10 37 0
	sbi 0xb,6
	.loc 10 38 0
	sbi 0xa,6
.LBE262:
.LBE261:
	.loc 6 119 0
	call USB_Init
.LVL84:
.LBB263:
.LBB264:
	.file 11 "../../LUFA/Drivers/Peripheral/Serial.h"
	.loc 11 102 0
	ldi r24,lo8(103)
	ldi r25,0
	sts 204+1,r25
	sts 204,r24
	.loc 11 104 0
	ldi r24,lo8(6)
	sts 202,r24
	.loc 11 105 0
	sts 200,__zero_reg__
	.loc 11 106 0
	ldi r24,lo8(24)
	sts 201,r24
	.loc 11 108 0
	sbi 0xa,3
	.loc 11 109 0
	sbi 0xb,2
.LVL85:
.LBE264:
.LBE263:
.LBB265:
.LBB266:
	.file 12 "../../LUFA/Drivers/Board/../Peripheral/SPI.h"
	.loc 12 124 0
	in r24,0x4
	ori r24,lo8(6)
	out 0x4,r24
	.loc 12 125 0
	in r24,0x4
	andi r24,lo8(-10)
	out 0x4,r24
	.loc 12 126 0
	in r24,0x5
	ori r24,lo8(9)
	out 0x5,r24
	.loc 12 128 0
	ldi r24,lo8(92)
	out 0x2c,r24
	.loc 12 131 0
	in r24,0x2d
	ori r24,lo8(1)
	out 0x2d,r24
.LVL86:
.LBE266:
.LBE265:
.LBB267:
.LBB268:
	.loc 3 134 0
	sbi 0x8,6
	.loc 3 135 0
	sbi 0x7,6
	.loc 3 137 0
	sbi 0x8,7
	.loc 3 138 0
	sbi 0x7,7
.LBE268:
.LBE267:
	.loc 6 125 0
	ldi r24,lo8(4)
	out 0x25,r24
.LBB269:
.LBB270:
	.file 13 "./Board/LEDs.h"
	.loc 13 34 0
	in r24,0xb
	ori r24,lo8(48)
	out 0xb,r24
	.loc 13 35 0
	in r24,0xa
	ori r24,lo8(48)
	out 0xa,r24
.LBE270:
.LBE269:
.LBB271:
.LBB272:
	.loc 5 191 0
	sbi 0x8,2
	.loc 5 192 0
	cbi 0x7,2
	.loc 5 193 0
	sbi 0x8,4
	.loc 5 194 0
	cbi 0x7,4
	.loc 5 195 0
	sbi 0x8,5
	.loc 5 196 0
	cbi 0x7,5
	.loc 5 197 0
	sbi 0x5,7
	.loc 5 198 0
	cbi 0x4,7
	.loc 5 201 0
	lds r24,104
	ori r24,lo8(1)
	sts 104,r24
	.loc 5 202 0
	lds r24,104
	ori r24,lo8(2)
	sts 104,r24
	.loc 5 205 0
	lds r24,108
	ori r24,lo8(8)
	sts 108,r24
.LVL87:
.LBE272:
.LBE271:
.LBB273:
.LBB274:
	.loc 9 45 0
	cbi 0x5,5
.LVL88:
.LBB275:
.LBB276:
	.loc 12 168 0
	ldi r24,lo8(35)
	out 0x2e,r24
.L38:
	.loc 12 169 0
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L38
.LVL89:
.LBE276:
.LBE275:
.LBB277:
.LBB278:
	.loc 12 168 0
	ldi r24,lo8(-94)
	out 0x2e,r24
.L39:
	.loc 12 169 0
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L39
.LVL90:
.LBE278:
.LBE277:
	.loc 9 48 0
	sbi 0x5,5
	.loc 9 51 0
	in r25,0x5
	ldi r24,lo8(64)
	eor r25,r24
	out 0x5,r25
	.loc 9 52 0
	in r25,0x5
	eor r24,r25
	out 0x5,r24
.LVL91:
.LBE274:
.LBE273:
.LBB279:
.LBB280:
	.loc 9 45 0
	cbi 0x5,5
.LVL92:
.LBB281:
.LBB282:
	.loc 12 168 0
	ldi r24,lo8(54)
	out 0x2e,r24
.L40:
	.loc 12 169 0
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L40
.LVL93:
.LBE282:
.LBE281:
.LBB283:
.LBB284:
	.loc 12 168 0
	ldi r24,lo8(15)
	out 0x2e,r24
.L41:
	.loc 12 169 0
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L41
.LVL94:
.LBE284:
.LBE283:
	.loc 9 48 0
	sbi 0x5,5
	.loc 9 51 0
	in r25,0x5
	ldi r24,lo8(64)
	eor r25,r24
	out 0x5,r25
	.loc 9 52 0
	in r25,0x5
	eor r24,r25
	out 0x5,r24
.LVL95:
	ret
.LBE280:
.LBE279:
	.cfi_endproc
.LFE170:
	.size	SetupHardware, .-SetupHardware
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB169:
	.loc 6 41 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 6 42 0
	call SetupHardware
.LVL96:
.LBB322:
	.loc 6 67 0
	ldi r17,lo8(3)
.L61:
.LVL97:
.LBB323:
.LBB324:
.LBB325:
.LBB326:
	.loc 1 57 0
	in r18,__SREG__
.LVL98:
.LBB327:
.LBB328:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL99:
/* #NOAPP */
.LBE328:
.LBE327:
	.loc 1 59 0
	lds r24,USBtoUSART_Buffer+132
	lds r25,USBtoUSART_Buffer+132+1
.LVL100:
.LBB329:
.LBB330:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL101:
.LBE330:
.LBE329:
.LBE326:
.LBE325:
.LBE324:
.LBE323:
	.loc 6 48 0
	cpi r24,-128
	cpc r25,__zero_reg__
	breq .L48
.LBB331:
	.loc 6 50 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_ReceiveByte
.LVL102:
	movw r28,r24
.LVL103:
	.loc 6 53 0
	sbrc r25,7
	rjmp .L48
	.loc 6 54 0
	mov r22,r24
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL104:
	call RingBuffer_Insert
.LVL105:
	.loc 6 55 0
	mov r22,r28
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Insert
.LVL106:
.L48:
.LBE331:
.LBB332:
.LBB333:
.LBB334:
	.loc 1 57 0
	in r24,__SREG__
.LVL107:
.LBB335:
.LBB336:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL108:
/* #NOAPP */
.LBE336:
.LBE335:
	.loc 1 59 0
	lds r28,USARTtoUSB_Buffer+132
	lds r29,USARTtoUSB_Buffer+132+1
.LVL109:
.LBB337:
.LBB338:
	.loc 2 70 0
	out __SREG__,r24
	.loc 2 71 0
.LVL110:
.LBE338:
.LBE337:
.LBE334:
.LBE333:
.LBE332:
	.loc 6 61 0
	sbic 0x15,0
	rjmp .L50
	.loc 6 61 0 is_stmt 0 discriminator 1
	cpi r28,97
	cpc r29,__zero_reg__
	brlo .L51
.L50:
	.loc 6 63 0 is_stmt 1
	sbi 0x15,0
	.loc 6 65 0
	lds r24,USARTtoUSB_Buffer+132
	lds r25,USARTtoUSB_Buffer+132+1
	or r24,r25
	breq .L53
.LVL111:
.LBB339:
.LBB340:
	.loc 13 46 0
	cbi 0xb,5
.LVL112:
.LBE340:
.LBE339:
	.loc 6 67 0
	sts TxLEDPulse,r17
.L53:
.LVL113:
	.loc 6 71 0
	sbiw r28,0
	breq .L73
	.loc 6 72 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Remove
.LVL114:
	mov r22,r24
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_SendByte
.LVL115:
	sbiw r28,1
.LVL116:
	rjmp .L53
.LVL117:
.L73:
	.loc 6 75 0
	lds r24,TxLEDPulse
	tst r24
	breq .L56
	.loc 6 75 0 is_stmt 0 discriminator 1
	subi r24,lo8(-(-1))
	sts TxLEDPulse,r24
	cpse r24,__zero_reg__
	rjmp .L56
.LVL118:
.LBB341:
.LBB342:
	.loc 13 51 0 is_stmt 1
	sbi 0xb,5
.LVL119:
.L56:
.LBE342:
.LBE341:
	.loc 6 79 0
	lds r24,RxLEDPulse
	tst r24
	breq .L51
	.loc 6 79 0 is_stmt 0 discriminator 1
	subi r24,lo8(-(-1))
	sts RxLEDPulse,r24
	cpse r24,__zero_reg__
	rjmp .L51
.LVL120:
.LBB343:
.LBB344:
	.loc 13 51 0 is_stmt 1
	sbi 0xb,4
.LVL121:
.L51:
.LBE344:
.LBE343:
.LBB345:
.LBB346:
.LBB347:
.LBB348:
	.loc 1 57 0
	in r18,__SREG__
.LVL122:
.LBB349:
.LBB350:
	.loc 2 50 0
/* #APP */
 ;  50 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL123:
/* #NOAPP */
.LBE350:
.LBE349:
	.loc 1 59 0
	lds r24,USBtoUSART_Buffer+132
	lds r25,USBtoUSART_Buffer+132+1
.LVL124:
.LBB351:
.LBB352:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL125:
.LBE352:
.LBE351:
.LBE348:
.LBE347:
.LBE346:
.LBE345:
	.loc 6 84 0
	or r24,r25
	breq .L59
	.loc 6 85 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	call RingBuffer_Remove
.LVL126:
.L60:
.LBB353:
.LBB354:
	.loc 11 142 0
	lds r25,200
	sbrs r25,5
	rjmp .L60
	.loc 11 143 0
	sts 206,r24
.LVL127:
.LBE354:
.LBE353:
.LBB355:
.LBB356:
	.loc 13 46 0
	cbi 0xb,4
.LVL128:
.LBE356:
.LBE355:
	.loc 6 88 0
	sts RxLEDPulse,r17
.L59:
	.loc 6 91 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_USBTask
.LVL129:
	.loc 6 92 0
	call USB_USBTask
.LVL130:
.LBE322:
	.loc 6 93 0
	rjmp .L61
	.cfi_endproc
.LFE169:
	.size	main, .-main
	.section	.text.Write_Program,"ax",@progbits
.global	Write_Program
	.type	Write_Program, @function
Write_Program:
.LFB171:
	.loc 6 149 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LBB368:
.LBB369:
	.loc 3 265 0
	sbi 0x8,6
	.loc 3 266 0
	ldi r24,lo8(50)
	call SW_PulseClock
.LVL131:
	.loc 3 267 0
	ldi r20,lo8(16)
	ldi r22,lo8(-98)
	ldi r23,lo8(-25)
	ldi r24,0
	ldi r25,0
	call SW_Send
.LVL132:
	.loc 3 268 0
	sbi 0x8,6
	.loc 3 269 0
	ldi r24,lo8(50)
	call SW_PulseClock
.LVL133:
.LBE369:
.LBE368:
.LBB370:
.LBB371:
.LBB372:
	.loc 3 169 0
	sbi 0x8,6
	.loc 3 170 0
	ldi r24,lo8(50)
	call SW_PulseClock
.LVL134:
	.loc 3 171 0
	cbi 0x8,6
	.loc 3 172 0
	ldi r24,lo8(50)
	call SW_PulseClock
.LVL135:
.LBE372:
.LBE371:
.LBB373:
.LBB374:
	.loc 3 228 0
	ldi r22,0
	ldi r23,0
	movw r24,r22
	call getParity
.LVL136:
	ldi r22,lo8(4)
	ldi r23,0
	ldi r24,0
	ldi r25,0
	call getParity
.LVL137:
	.loc 3 229 0
	swap r24
.LVL138:
	lsl r24
	andi r24,lo8(-32)
	ori r24,lo8(-123)
.LVL139:
	.loc 3 240 0
	mov r12,r24
	mov r13,__zero_reg__
	mov r14,__zero_reg__
	mov r15,__zero_reg__
.LBB375:
.LBB376:
.LBB377:
	.loc 3 206 0
	ldi r16,lo8(1)
	ldi r17,0
.LVL140:
.L77:
.LBE377:
.LBE376:
.LBE375:
	.loc 3 240 0
	ldi r20,lo8(8)
	movw r24,r14
	movw r22,r12
	call SW_Send
.LVL141:
	.loc 3 241 0
	ldi r24,lo8(1)
	call SW_PulseClock
.LVL142:
.LBB380:
.LBB379:
	.loc 3 201 0
	sbi 0x8,6
	.loc 3 202 0
	cbi 0x7,6
.LVL143:
	ldi r28,0
	ldi r29,0
	.loc 3 198 0
	mov r8,__zero_reg__
	mov r9,__zero_reg__
	movw r10,r8
.LVL144:
.L76:
.LBB378:
	.loc 3 206 0
	sbis 0x6,6
	rjmp .L79
	movw r24,r16
	mov r0,r28
	rjmp 2f
	1:
	lsl r24
	rol r25
	2:
	dec r0
	brpl 1b
	rjmp .L75
.L79:
	ldi r24,0
	ldi r25,0
.L75:
	mov __tmp_reg__,r25
	lsl r0
	sbc r26,r26
	sbc r27,r27
	or r8,r24
	or r9,r25
	or r10,r26
	or r11,r27
.LVL145:
	.loc 3 207 0
	ldi r24,lo8(1)
	call SW_PulseClock
.LVL146:
	adiw r28,1
.LVL147:
	.loc 3 205 0
	cpi r28,3
	cpc r29,__zero_reg__
	brne .L76
.LBE378:
	.loc 3 211 0
	sbi 0x8,6
	.loc 3 212 0
	sbi 0x7,6
.LVL148:
.LBE379:
.LBE380:
	.loc 3 242 0
	ldi r24,lo8(2)
	cpse r8,r24
	rjmp .L77
	.loc 3 243 0
	ldi r24,lo8(1)
	call SW_PulseClock
.LVL149:
	rjmp .L77
.LBE374:
.LBE373:
.LBE370:
	.cfi_endproc
.LFE171:
	.size	Write_Program, .-Write_Program
	.section	.text.EVENT_USB_Device_ConfigurationChanged,"ax",@progbits
.global	EVENT_USB_Device_ConfigurationChanged
	.type	EVENT_USB_Device_ConfigurationChanged, @function
EVENT_USB_Device_ConfigurationChanged:
.LFB172:
	.loc 6 169 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 6 170 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ConfigureEndpoints
.LVL150:
	.cfi_endproc
.LFE172:
	.size	EVENT_USB_Device_ConfigurationChanged, .-EVENT_USB_Device_ConfigurationChanged
	.section	.text.EVENT_USB_Device_UnhandledControlRequest,"ax",@progbits
.global	EVENT_USB_Device_UnhandledControlRequest
	.type	EVENT_USB_Device_UnhandledControlRequest, @function
EVENT_USB_Device_UnhandledControlRequest:
.LFB173:
	.loc 6 175 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 6 176 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ProcessControlRequest
.LVL151:
	.cfi_endproc
.LFE173:
	.size	EVENT_USB_Device_UnhandledControlRequest, .-EVENT_USB_Device_UnhandledControlRequest
	.section	.text.EVENT_CDC_Device_LineEncodingChanged,"ax",@progbits
.global	EVENT_CDC_Device_LineEncodingChanged
	.type	EVENT_CDC_Device_LineEncodingChanged, @function
EVENT_CDC_Device_LineEncodingChanged:
.LFB174:
	.loc 6 185 0
	.cfi_startproc
.LVL152:
	push r28
.LCFI32:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI33:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r28,r24
	.loc 6 187 0
	sts 201,__zero_reg__
	.loc 6 190 0
	ldd r18,Y+15
	ldd r19,Y+16
	ldd r20,Y+17
	ldd r21,Y+18
	movw r26,r20
	movw r24,r18
.LVL153:
	lsr r27
	ror r26
	ror r25
	ror r24
	movw r22,r24
	movw r24,r26
	subi r22,-128
	sbci r23,123
	sbci r24,-31
	sbci r25,-1
	call __udivmodsi4
	subi r18,1
	sbc r19,__zero_reg__
	sts 204+1,r19
	sts 204,r18
.LVL154:
.LBB381:
	.loc 6 197 0
	ldd r24,Y+20
	cpi r24,lo8(1)
	breq .L86
	cpi r24,lo8(2)
	brne .L95
.LVL155:
	.loc 6 199 0
	ldi r24,lo8(32)
	rjmp .L85
.LVL156:
.L86:
	.loc 6 198 0
	ldi r24,lo8(48)
	rjmp .L85
.L95:
	.loc 6 194 0
	ldi r24,0
.LVL157:
.L85:
	.loc 6 203 0
	ldd r25,Y+19
	cpi r25,lo8(2)
	brne .L88
	.loc 6 204 0
	ori r24,lo8(8)
.LVL158:
.L88:
	.loc 6 207 0
	ldd r25,Y+21
	cpi r25,lo8(7)
	breq .L90
	cpi r25,lo8(8)
	breq .L91
	cpi r25,lo8(6)
	brne .L89
	.loc 6 208 0
	ori r24,lo8(2)
.LVL159:
	rjmp .L89
.L90:
	.loc 6 209 0
	ori r24,lo8(4)
.LVL160:
	rjmp .L89
.L91:
	.loc 6 210 0
	ori r24,lo8(6)
.LVL161:
.L89:
	.loc 6 213 0
	sts 202,r24
.LBE381:
	.loc 6 217 0
	ldi r24,lo8(2)
.LVL162:
	sts 200,r24
.LVL163:
	.loc 6 220 0
	ldi r24,lo8(-104)
	sts 201,r24
/* epilogue start */
	.loc 6 221 0
	pop r29
	pop r28
.LVL164:
	ret
	.cfi_endproc
.LFE174:
	.size	EVENT_CDC_Device_LineEncodingChanged, .-EVENT_CDC_Device_LineEncodingChanged
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"ICSRL>"
	.section	.text.EVENT_CDC_Device_ControLineStateChanged,"ax",@progbits
.global	EVENT_CDC_Device_ControLineStateChanged
	.type	EVENT_CDC_Device_ControLineStateChanged, @function
EVENT_CDC_Device_ControLineStateChanged:
.LFB175:
	.loc 6 228 0
	.cfi_startproc
.LVL165:
	push r28
.LCFI34:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI35:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
.LVL166:
	.loc 6 232 0
	movw r30,r24
	ldd r24,Z+13
.LVL167:
	sbrs r24,0
	rjmp .L97
	ldi r28,lo8(.LC0)
	ldi r29,hi8(.LC0)
.LVL168:
.L98:
.LBB385:
.LBB386:
	.file 14 "Lib/UARTConsole.h"
	.loc 14 22 0
	ld r22,Y+
.LVL169:
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_SendByte
.LVL170:
	.loc 14 21 0
	ldi r31,hi8(.LC0+6)
	cpi r28,lo8(.LC0+6)
	cpc r29,r31
	brne .L98
.LVL171:
.LBE386:
.LBE385:
	.loc 6 234 0
	cbi 0xb,7
	rjmp .L96
.LVL172:
.L97:
	.loc 6 237 0
	sbi 0xb,7
.LVL173:
.L96:
/* epilogue start */
	.loc 6 239 0
	pop r29
	pop r28
	ret
	.cfi_endproc
.LFE175:
	.size	EVENT_CDC_Device_ControLineStateChanged, .-EVENT_CDC_Device_ControLineStateChanged
	.section	.text.__vector_23,"ax",@progbits
.global	__vector_23
	.type	__vector_23, @function
__vector_23:
.LFB176:
	.loc 6 247 0
	.cfi_startproc
	push r1
.LCFI36:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI37:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI38:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI39:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI40:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI41:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI42:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r23
.LCFI43:
	.cfi_def_cfa_offset 10
	.cfi_offset 23, -9
	push r24
.LCFI44:
	.cfi_def_cfa_offset 11
	.cfi_offset 24, -10
	push r25
.LCFI45:
	.cfi_def_cfa_offset 12
	.cfi_offset 25, -11
	push r26
.LCFI46:
	.cfi_def_cfa_offset 13
	.cfi_offset 26, -12
	push r27
.LCFI47:
	.cfi_def_cfa_offset 14
	.cfi_offset 27, -13
	push r30
.LCFI48:
	.cfi_def_cfa_offset 15
	.cfi_offset 30, -14
	push r31
.LCFI49:
	.cfi_def_cfa_offset 16
	.cfi_offset 31, -15
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	.loc 6 249 0
	lds r22,206
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Insert
.LVL174:
/* epilogue start */
	.loc 6 250 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE176:
	.size	__vector_23, .-__vector_23
.global	VirtualSerial_CDC_Interface
	.data
	.type	VirtualSerial_CDC_Interface, @object
	.size	VirtualSerial_CDC_Interface, 22
VirtualSerial_CDC_Interface:
	.byte	0
	.byte	3
	.word	64
	.byte	0
	.byte	4
	.word	64
	.byte	0
	.byte	2
	.word	8
	.byte	0
	.zero	9
	.comm	USARTtoUSB_Buffer,134,1
	.comm	USBtoUSART_Buffer,134,1
	.comm	command,64,1
	.comm	RxLEDPulse,1,1
	.comm	TxLEDPulse,1,1
	.text
.Letext0:
	.file 15 "/nethome/mchang87/Projects/RRAM/atmega16u2/avr8-gnu-toolchain-linux_x86_64/avr/include/stdint.h"
	.file 16 "../../LUFA/Drivers/USB/Class/Device/../Common/CDC.h"
	.file 17 "../../LUFA/Drivers/USB/Class/Device/CDC.h"
	.file 18 "../../LUFA/Drivers/Board/Dataflash.h"
	.file 19 "../../LUFA/Drivers/USB/HighLevel/../LowLevel/USBController.h"
	.file 20 "../../LUFA/Drivers/USB/HighLevel/USBTask.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x18e2
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF167
	.byte	0xc
	.long	.LASF168
	.long	.LASF169
	.long	.Ldebug_ranges0+0x48
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF0
	.byte	0xf
	.byte	0x7d
	.long	0x34
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF1
	.byte	0xf
	.byte	0x7e
	.long	0x46
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x2
	.long	.LASF4
	.byte	0xf
	.byte	0x7f
	.long	0x58
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.long	.LASF5
	.byte	0xf
	.byte	0x80
	.long	0x6a
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF6
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.long	.LASF8
	.byte	0xf
	.byte	0x82
	.long	0x83
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF12
	.uleb128 0x5
	.long	.LASF16
	.byte	0x1
	.long	0x46
	.byte	0x10
	.byte	0xae
	.long	0xc2
	.uleb128 0x6
	.long	.LASF13
	.byte	0
	.uleb128 0x6
	.long	.LASF14
	.byte	0x1
	.uleb128 0x6
	.long	.LASF15
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.long	.LASF17
	.byte	0x1
	.long	0x46
	.byte	0x10
	.byte	0xb6
	.long	0xf1
	.uleb128 0x6
	.long	.LASF18
	.byte	0
	.uleb128 0x6
	.long	.LASF19
	.byte	0x1
	.uleb128 0x6
	.long	.LASF20
	.byte	0x2
	.uleb128 0x6
	.long	.LASF21
	.byte	0x3
	.uleb128 0x6
	.long	.LASF22
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF23
	.uleb128 0x7
	.byte	0xd
	.byte	0x11
	.byte	0x64
	.long	0x18d
	.uleb128 0x8
	.long	.LASF24
	.byte	0x11
	.byte	0x66
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF25
	.byte	0x11
	.byte	0x68
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF26
	.byte	0x11
	.byte	0x69
	.long	0x5f
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF27
	.byte	0x11
	.byte	0x6a
	.long	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF28
	.byte	0x11
	.byte	0x6c
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF29
	.byte	0x11
	.byte	0x6d
	.long	0x5f
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF30
	.byte	0x11
	.byte	0x6e
	.long	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF31
	.byte	0x11
	.byte	0x70
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x8
	.long	.LASF32
	.byte	0x11
	.byte	0x71
	.long	0x5f
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x8
	.long	.LASF33
	.byte	0x11
	.byte	0x72
	.long	0x18d
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.long	.LASF34
	.uleb128 0x7
	.byte	0x2
	.byte	0x11
	.byte	0x78
	.long	0x1b9
	.uleb128 0x8
	.long	.LASF35
	.byte	0x11
	.byte	0x7a
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF36
	.byte	0x11
	.byte	0x7d
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.byte	0x11
	.byte	0x83
	.long	0x1fa
	.uleb128 0x8
	.long	.LASF37
	.byte	0x11
	.byte	0x85
	.long	0x78
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF38
	.byte	0x11
	.byte	0x86
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF39
	.byte	0x11
	.byte	0x89
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF40
	.byte	0x11
	.byte	0x8c
	.long	0x3b
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.byte	0
	.uleb128 0x7
	.byte	0x9
	.byte	0x11
	.byte	0x76
	.long	0x21f
	.uleb128 0x8
	.long	.LASF41
	.byte	0x11
	.byte	0x81
	.long	0x194
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF42
	.byte	0x11
	.byte	0x8d
	.long	0x1b9
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x7
	.byte	0x16
	.byte	0x11
	.byte	0x62
	.long	0x244
	.uleb128 0x8
	.long	.LASF43
	.byte	0x11
	.byte	0x73
	.long	0x244
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF44
	.byte	0x11
	.byte	0x90
	.long	0x1fa
	.byte	0x2
	.byte	0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x9
	.long	0xf8
	.uleb128 0x2
	.long	.LASF45
	.byte	0x11
	.byte	0x93
	.long	0x21f
	.uleb128 0x7
	.byte	0x86
	.byte	0x1
	.byte	0xf
	.long	0x297
	.uleb128 0x8
	.long	.LASF46
	.byte	0x1
	.byte	0x11
	.long	0x297
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.string	"In"
	.byte	0x1
	.byte	0x12
	.long	0x2a7
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xa
	.string	"Out"
	.byte	0x1
	.byte	0x13
	.long	0x2a7
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0x8
	.long	.LASF47
	.byte	0x1
	.byte	0x14
	.long	0x5f
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.byte	0
	.uleb128 0xb
	.long	0x3b
	.long	0x2a7
	.uleb128 0xc
	.long	0x98
	.byte	0x7f
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x3b
	.uleb128 0x2
	.long	.LASF48
	.byte	0x1
	.byte	0x15
	.long	0x254
	.uleb128 0xe
	.long	.LASF49
	.byte	0xc
	.byte	0xa6
	.byte	0x1
	.byte	0x3
	.long	0x2d1
	.uleb128 0xf
	.long	.LASF51
	.byte	0xc
	.byte	0xa6
	.long	0x2d1
	.byte	0
	.uleb128 0x9
	.long	0x3b
	.uleb128 0x10
	.long	.LASF53
	.byte	0xc
	.byte	0xb2
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.uleb128 0xe
	.long	.LASF50
	.byte	0x12
	.byte	0xa8
	.byte	0x1
	.byte	0x3
	.long	0x2fc
	.uleb128 0xf
	.long	.LASF51
	.byte	0x12
	.byte	0xa8
	.long	0x2d1
	.byte	0
	.uleb128 0xe
	.long	.LASF52
	.byte	0x2
	.byte	0x44
	.byte	0x1
	.byte	0x3
	.long	0x315
	.uleb128 0x11
	.string	"__s"
	.byte	0x2
	.byte	0x44
	.long	0x315
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x2d1
	.uleb128 0x10
	.long	.LASF54
	.byte	0x2
	.byte	0x30
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.uleb128 0x12
	.long	.LASF57
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.long	0x5f
	.byte	0x3
	.long	0x368
	.uleb128 0xf
	.long	.LASF46
	.byte	0x1
	.byte	0x35
	.long	0x36e
	.uleb128 0x13
	.long	.LASF47
	.byte	0x1
	.byte	0x37
	.long	0x5f
	.uleb128 0x14
	.uleb128 0x13
	.long	.LASF55
	.byte	0x1
	.byte	0x39
	.long	0x3b
	.uleb128 0x13
	.long	.LASF56
	.byte	0x1
	.byte	0x39
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x2ad
	.uleb128 0x9
	.long	0x368
	.uleb128 0x12
	.long	.LASF58
	.byte	0x5
	.byte	0x66
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.long	0x39b
	.uleb128 0xf
	.long	.LASF59
	.byte	0x5
	.byte	0x66
	.long	0x39b
	.uleb128 0xf
	.long	.LASF60
	.byte	0x5
	.byte	0x66
	.long	0x39b
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.long	.LASF61
	.uleb128 0x12
	.long	.LASF62
	.byte	0x3
	.byte	0xdc
	.byte	0x1
	.long	0x78
	.byte	0x3
	.long	0x40c
	.uleb128 0xf
	.long	.LASF63
	.byte	0x3
	.byte	0xdc
	.long	0x3b
	.uleb128 0xf
	.long	.LASF64
	.byte	0x3
	.byte	0xdc
	.long	0x3b
	.uleb128 0xf
	.long	.LASF65
	.byte	0x3
	.byte	0xdc
	.long	0x3b
	.uleb128 0xf
	.long	.LASF66
	.byte	0x3
	.byte	0xdc
	.long	0x78
	.uleb128 0x13
	.long	.LASF67
	.byte	0x3
	.byte	0xde
	.long	0x3b
	.uleb128 0x15
	.string	"ack"
	.byte	0x3
	.byte	0xdf
	.long	0x3b
	.uleb128 0x13
	.long	.LASF68
	.byte	0x3
	.byte	0xe0
	.long	0x78
	.uleb128 0x13
	.long	.LASF69
	.byte	0x3
	.byte	0xe1
	.long	0x18d
	.byte	0
	.uleb128 0x16
	.long	.LASF70
	.byte	0x3
	.word	0x14c
	.byte	0x1
	.long	0x78
	.byte	0x3
	.long	0x443
	.uleb128 0x17
	.long	.LASF71
	.byte	0x3
	.word	0x14c
	.long	0x78
	.uleb128 0x17
	.long	.LASF72
	.byte	0x3
	.word	0x14c
	.long	0x78
	.uleb128 0x18
	.long	.LASF68
	.byte	0x3
	.word	0x157
	.long	0x78
	.byte	0
	.uleb128 0x19
	.long	.LASF73
	.byte	0x3
	.word	0x12b
	.byte	0x1
	.byte	0x3
	.long	0x482
	.uleb128 0x17
	.long	.LASF71
	.byte	0x3
	.word	0x12b
	.long	0x78
	.uleb128 0x17
	.long	.LASF72
	.byte	0x3
	.word	0x12b
	.long	0x78
	.uleb128 0x17
	.long	.LASF66
	.byte	0x3
	.word	0x12b
	.long	0x78
	.uleb128 0x18
	.long	.LASF68
	.byte	0x3
	.word	0x135
	.long	0x78
	.byte	0
	.uleb128 0xe
	.long	.LASF74
	.byte	0x9
	.byte	0x24
	.byte	0x1
	.byte	0x3
	.long	0x4c7
	.uleb128 0xf
	.long	.LASF75
	.byte	0x9
	.byte	0x24
	.long	0x3b
	.uleb128 0xf
	.long	.LASF76
	.byte	0x9
	.byte	0x24
	.long	0x3b
	.uleb128 0xf
	.long	.LASF77
	.byte	0x9
	.byte	0x24
	.long	0x5f
	.uleb128 0x13
	.long	.LASF78
	.byte	0x9
	.byte	0x27
	.long	0x5f
	.uleb128 0x13
	.long	.LASF79
	.byte	0x9
	.byte	0x2a
	.long	0x5f
	.byte	0
	.uleb128 0x19
	.long	.LASF80
	.byte	0x7
	.word	0x1ec
	.byte	0x1
	.byte	0x3
	.long	0x4e4
	.uleb128 0x14
	.uleb128 0x18
	.long	.LASF81
	.byte	0x7
	.word	0x202
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0xe
	.long	.LASF82
	.byte	0xb
	.byte	0x8c
	.byte	0x1
	.byte	0x3
	.long	0x4fd
	.uleb128 0xf
	.long	.LASF83
	.byte	0xb
	.byte	0x8c
	.long	0x4fd
	.byte	0
	.uleb128 0x9
	.long	0xf1
	.uleb128 0xe
	.long	.LASF84
	.byte	0xc
	.byte	0x7a
	.byte	0x1
	.byte	0x3
	.long	0x51b
	.uleb128 0xf
	.long	.LASF85
	.byte	0xc
	.byte	0x7a
	.long	0x2d1
	.byte	0
	.uleb128 0xe
	.long	.LASF86
	.byte	0xb
	.byte	0x63
	.byte	0x1
	.byte	0x3
	.long	0x53f
	.uleb128 0xf
	.long	.LASF87
	.byte	0xb
	.byte	0x63
	.long	0x53f
	.uleb128 0xf
	.long	.LASF88
	.byte	0xb
	.byte	0x64
	.long	0x544
	.byte	0
	.uleb128 0x9
	.long	0x78
	.uleb128 0x9
	.long	0x18d
	.uleb128 0x12
	.long	.LASF89
	.byte	0x1
	.byte	0x7b
	.byte	0x1
	.long	0x18d
	.byte	0x3
	.long	0x566
	.uleb128 0xf
	.long	.LASF46
	.byte	0x1
	.byte	0x7b
	.long	0x36e
	.byte	0
	.uleb128 0x12
	.long	.LASF90
	.byte	0x1
	.byte	0x8c
	.byte	0x1
	.long	0x18d
	.byte	0x3
	.long	0x583
	.uleb128 0xf
	.long	.LASF46
	.byte	0x1
	.byte	0x8c
	.long	0x36e
	.byte	0
	.uleb128 0x12
	.long	.LASF91
	.byte	0x3
	.byte	0xc4
	.byte	0x1
	.long	0x78
	.byte	0x3
	.long	0x5b6
	.uleb128 0xf
	.long	.LASF92
	.byte	0x3
	.byte	0xc4
	.long	0x3b
	.uleb128 0x13
	.long	.LASF93
	.byte	0x3
	.byte	0xc6
	.long	0x78
	.uleb128 0x14
	.uleb128 0x15
	.string	"i"
	.byte	0x3
	.byte	0xcd
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0xe
	.long	.LASF94
	.byte	0x5
	.byte	0x6e
	.byte	0x1
	.byte	0x3
	.long	0x5cf
	.uleb128 0xf
	.long	.LASF59
	.byte	0x5
	.byte	0x6e
	.long	0x39b
	.byte	0
	.uleb128 0xe
	.long	.LASF95
	.byte	0x5
	.byte	0x6f
	.byte	0x1
	.byte	0x3
	.long	0x5e8
	.uleb128 0xf
	.long	.LASF59
	.byte	0x5
	.byte	0x6f
	.long	0x39b
	.byte	0
	.uleb128 0xe
	.long	.LASF96
	.byte	0x5
	.byte	0x70
	.byte	0x1
	.byte	0x3
	.long	0x601
	.uleb128 0xf
	.long	.LASF59
	.byte	0x5
	.byte	0x70
	.long	0x39b
	.byte	0
	.uleb128 0xe
	.long	.LASF97
	.byte	0x5
	.byte	0x71
	.byte	0x1
	.byte	0x3
	.long	0x61a
	.uleb128 0xf
	.long	.LASF59
	.byte	0x5
	.byte	0x71
	.long	0x39b
	.byte	0
	.uleb128 0x1a
	.long	.LASF99
	.byte	0x1
	.byte	0x4b
	.byte	0x1
	.long	.LFB104
	.long	.LFE104
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x6a3
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.byte	0x4b
	.long	0x36e
	.long	.LLST0
	.uleb128 0x1c
	.long	.LASF98
	.byte	0x1
	.byte	0x4c
	.long	0x2d1
	.byte	0x1
	.byte	0x66
	.uleb128 0x1d
	.long	.LBB92
	.long	.LBE92
	.uleb128 0x1e
	.long	.LASF55
	.byte	0x1
	.byte	0x53
	.long	0x3b
	.long	.LLST1
	.uleb128 0x1e
	.long	.LASF56
	.byte	0x1
	.byte	0x53
	.long	0x3b
	.long	.LLST2
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB93
	.long	.LBE93
	.byte	0x1
	.byte	0x53
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB95
	.long	.LBE95
	.byte	0x1
	.byte	0x53
	.uleb128 0x21
	.long	0x309
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1624
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x22
	.long	.LASF105
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.long	0x3b
	.long	.LFB105
	.long	.LFE105
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x730
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.byte	0x64
	.long	0x36e
	.long	.LLST3
	.uleb128 0x23
	.long	.LASF98
	.byte	0x1
	.byte	0x66
	.long	0x3b
	.byte	0x1
	.byte	0x64
	.uleb128 0x1d
	.long	.LBB97
	.long	.LBE97
	.uleb128 0x1e
	.long	.LASF55
	.byte	0x1
	.byte	0x6b
	.long	0x3b
	.long	.LLST4
	.uleb128 0x1e
	.long	.LASF56
	.byte	0x1
	.byte	0x6b
	.long	0x3b
	.long	.LLST5
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB98
	.long	.LBE98
	.byte	0x1
	.byte	0x6b
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB100
	.long	.LBE100
	.byte	0x1
	.byte	0x6b
	.uleb128 0x21
	.long	0x309
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1765
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
	.long	.LASF100
	.byte	0x3
	.byte	0x9c
	.byte	0x1
	.long	.LFB118
	.long	.LFE118
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x76e
	.uleb128 0x1c
	.long	.LASF101
	.byte	0x3
	.byte	0x9c
	.long	0x3b
	.byte	0x1
	.byte	0x68
	.uleb128 0x1d
	.long	.LBB102
	.long	.LBE102
	.uleb128 0x24
	.string	"i"
	.byte	0x3
	.byte	0x9e
	.long	0x3b
	.long	.LLST6
	.byte	0
	.byte	0
	.uleb128 0x25
	.long	.LASF102
	.byte	0x3
	.byte	0xb2
	.byte	0x1
	.long	.LFB120
	.long	.LFE120
	.long	.LLST7
	.byte	0x1
	.long	0x7cc
	.uleb128 0x1b
	.long	.LASF66
	.byte	0x3
	.byte	0xb2
	.long	0x78
	.long	.LLST8
	.uleb128 0x1b
	.long	.LASF92
	.byte	0x3
	.byte	0xb2
	.long	0x3b
	.long	.LLST9
	.uleb128 0x1d
	.long	.LBB103
	.long	.LBE103
	.uleb128 0x24
	.string	"i"
	.byte	0x3
	.byte	0xb5
	.long	0x3b
	.long	.LLST10
	.uleb128 0x26
	.long	.LVL19
	.long	0x730
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	.LASF103
	.byte	0x4
	.byte	0x1e
	.byte	0x1
	.long	.LFB133
	.long	.LFE133
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x28
	.long	.LASF104
	.byte	0x4
	.byte	0x2c
	.byte	0x1
	.long	.LFB134
	.long	.LFE134
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x22
	.long	.LASF106
	.byte	0x4
	.byte	0x39
	.byte	0x1
	.long	0x18d
	.long	.LFB135
	.long	.LFE135
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x849
	.uleb128 0x1b
	.long	.LASF66
	.byte	0x4
	.byte	0x39
	.long	0x3b
	.long	.LLST11
	.uleb128 0x24
	.string	"ack"
	.byte	0x4
	.byte	0x49
	.long	0x18d
	.long	.LLST12
	.uleb128 0x1d
	.long	.LBB104
	.long	.LBE104
	.uleb128 0x24
	.string	"i"
	.byte	0x4
	.byte	0x3c
	.long	0x29
	.long	.LLST13
	.byte	0
	.byte	0
	.uleb128 0xe
	.long	.LASF107
	.byte	0x5
	.byte	0x42
	.byte	0x1
	.byte	0x3
	.long	0x86d
	.uleb128 0xf
	.long	.LASF108
	.byte	0x5
	.byte	0x42
	.long	0x3b
	.uleb128 0xf
	.long	.LASF66
	.byte	0x5
	.byte	0x42
	.long	0x3b
	.byte	0
	.uleb128 0x12
	.long	.LASF109
	.byte	0x5
	.byte	0x4e
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.long	0x895
	.uleb128 0xf
	.long	.LASF108
	.byte	0x5
	.byte	0x4e
	.long	0x3b
	.uleb128 0x13
	.long	.LASF93
	.byte	0x5
	.byte	0x50
	.long	0x3b
	.byte	0
	.uleb128 0x12
	.long	.LASF110
	.byte	0x4
	.byte	0x57
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.long	0x8bd
	.uleb128 0x13
	.long	.LASF93
	.byte	0x4
	.byte	0x59
	.long	0x3b
	.uleb128 0x14
	.uleb128 0x15
	.string	"i"
	.byte	0x4
	.byte	0x60
	.long	0x29
	.byte	0
	.byte	0
	.uleb128 0x25
	.long	.LASF111
	.byte	0x5
	.byte	0x5e
	.byte	0x1
	.long	.LFB139
	.long	.LFE139
	.long	.LLST14
	.byte	0x1
	.long	0xa3b
	.uleb128 0x1b
	.long	.LASF108
	.byte	0x5
	.byte	0x5e
	.long	0x3b
	.long	.LLST15
	.uleb128 0x1b
	.long	.LASF66
	.byte	0x5
	.byte	0x5e
	.long	0x3b
	.long	.LLST16
	.uleb128 0x1b
	.long	.LASF112
	.byte	0x5
	.byte	0x5e
	.long	0x3b
	.long	.LLST17
	.uleb128 0x29
	.long	0x86d
	.long	.LBB112
	.long	.LBE112
	.byte	0x5
	.byte	0x60
	.long	0x9c2
	.uleb128 0x2a
	.long	0x87e
	.long	.LLST18
	.uleb128 0x1d
	.long	.LBB113
	.long	.LBE113
	.uleb128 0x2b
	.long	0x889
	.byte	0x1
	.byte	0x6c
	.uleb128 0x29
	.long	0x895
	.long	.LBB114
	.long	.LBE114
	.byte	0x5
	.byte	0x56
	.long	0x969
	.uleb128 0x1d
	.long	.LBB115
	.long	.LBE115
	.uleb128 0x2c
	.long	0x8a6
	.long	.LLST19
	.uleb128 0x1d
	.long	.LBB116
	.long	.LBE116
	.uleb128 0x2c
	.long	0x8b2
	.long	.LLST20
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2d
	.long	.LVL32
	.long	0x7cc
	.uleb128 0x2e
	.long	.LVL33
	.long	0x7f6
	.long	0x986
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x78
	.byte	0
	.uleb128 0x2e
	.long	.LVL34
	.long	0x7f6
	.long	0x99a
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x81
	.sleb128 0
	.byte	0
	.uleb128 0x2d
	.long	.LVL35
	.long	0x7cc
	.uleb128 0x2e
	.long	.LVL36
	.long	0x7f6
	.long	0x9b7
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x79
	.byte	0
	.uleb128 0x2d
	.long	.LVL43
	.long	0x7e1
	.byte	0
	.byte	0
	.uleb128 0x2f
	.long	0x849
	.long	.LBB117
	.long	.Ldebug_ranges0+0
	.byte	0x5
	.byte	0x60
	.uleb128 0x2a
	.long	0x861
	.long	.LLST21
	.uleb128 0x2a
	.long	0x856
	.long	.LLST22
	.uleb128 0x2d
	.long	.LVL44
	.long	0x7cc
	.uleb128 0x2e
	.long	.LVL45
	.long	0x7f6
	.long	0xa00
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x78
	.byte	0
	.uleb128 0x2e
	.long	.LVL46
	.long	0x7f6
	.long	0xa14
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x81
	.sleb128 0
	.byte	0
	.uleb128 0x2e
	.long	.LVL48
	.long	0x7f6
	.long	0xa2f
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x9
	.byte	0x8d
	.sleb128 0
	.byte	0x20
	.byte	0x8c
	.sleb128 0
	.byte	0x1a
	.byte	0x80
	.sleb128 0
	.byte	0x21
	.byte	0
	.uleb128 0x30
	.long	.LVL53
	.byte	0x1
	.long	0x7e1
	.byte	0
	.byte	0
	.uleb128 0x31
	.byte	0x1
	.long	.LASF144
	.byte	0x3
	.byte	0x77
	.byte	0x1
	.long	0x18d
	.long	.LFB115
	.long	.LFE115
	.long	.LLST23
	.byte	0x1
	.long	0xa76
	.uleb128 0x32
	.string	"n"
	.byte	0x3
	.byte	0x77
	.long	0x78
	.long	.LLST24
	.uleb128 0x1e
	.long	.LASF69
	.byte	0x3
	.byte	0x79
	.long	0x18d
	.long	.LLST25
	.byte	0
	.uleb128 0x33
	.byte	0x1
	.long	.LASF170
	.byte	0x5
	.byte	0xd6
	.byte	0x1
	.long	.LFB163
	.long	.LFE163
	.long	.LLST26
	.byte	0x1
	.uleb128 0x34
	.long	.LASF113
	.byte	0x5
	.byte	0x95
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF114
	.byte	0x5
	.byte	0x78
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF115
	.byte	0x5
	.byte	0x77
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF116
	.byte	0x5
	.byte	0x76
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF117
	.byte	0x5
	.byte	0x79
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF118
	.byte	0x5
	.byte	0x7b
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF119
	.byte	0x5
	.byte	0x7a
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF120
	.byte	0x5
	.byte	0xac
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF121
	.byte	0x5
	.byte	0x83
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF122
	.byte	0x5
	.byte	0x85
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF123
	.byte	0x5
	.byte	0x84
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF124
	.byte	0x5
	.byte	0x82
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF125
	.byte	0x5
	.byte	0x81
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF126
	.byte	0x5
	.byte	0x80
	.byte	0x1
	.byte	0x3
	.uleb128 0x35
	.byte	0x1
	.long	.LASF134
	.byte	0x5
	.byte	0xd9
	.byte	0x1
	.long	.LFB164
	.long	.LFE164
	.long	.LLST27
	.byte	0x1
	.long	0xe14
	.uleb128 0x29
	.long	0xa8c
	.long	.LBB165
	.long	.LBE165
	.byte	0x5
	.byte	0xdb
	.long	0xd06
	.uleb128 0x29
	.long	0x5b6
	.long	.LBB166
	.long	.LBE166
	.byte	0x5
	.byte	0x99
	.long	0xb6d
	.uleb128 0x2a
	.long	0x5c3
	.long	.LLST28
	.uleb128 0x26
	.long	.LVL60
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x3a
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x43
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x4f
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x5e8
	.long	.LBB168
	.long	.LBE168
	.byte	0x5
	.byte	0x9a
	.long	0xba3
	.uleb128 0x2a
	.long	0x5f5
	.long	.LLST29
	.uleb128 0x26
	.long	.LVL61
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x3e
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x48
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x4f
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x5cf
	.long	.LBB170
	.long	.LBE170
	.byte	0x5
	.byte	0x9b
	.long	0xbd9
	.uleb128 0x2a
	.long	0x5dc
	.long	.LLST30
	.uleb128 0x26
	.long	.LVL62
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x3c
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x4d
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x4f
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x601
	.long	.LBB172
	.long	.LBE172
	.byte	0x5
	.byte	0x9c
	.long	0xc0f
	.uleb128 0x2a
	.long	0x60e
	.long	.LLST31
	.uleb128 0x26
	.long	.LVL63
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x40
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x3b
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x4f
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xac2
	.long	.LBB174
	.long	.LBE174
	.byte	0x5
	.byte	0x9f
	.long	0xc3c
	.uleb128 0x26
	.long	.LVL64
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x35
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x34
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xab9
	.long	.LBB176
	.long	.LBE176
	.byte	0x5
	.byte	0xa0
	.long	0xc69
	.uleb128 0x26
	.long	.LVL65
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x36
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x34
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xab0
	.long	.LBB178
	.long	.LBE178
	.byte	0x5
	.byte	0xa1
	.long	0xc98
	.uleb128 0x26
	.long	.LVL66
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x34
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xaa7
	.long	.LBB180
	.long	.LBE180
	.byte	0x5
	.byte	0xa4
	.long	0xcc7
	.uleb128 0x26
	.long	.LVL67
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xa9e
	.long	.LBB182
	.long	.LBE182
	.byte	0x5
	.byte	0xa5
	.long	0xcf6
	.uleb128 0x26
	.long	.LVL68
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x32
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0xa95
	.long	.LBB184
	.long	.LBE184
	.byte	0x5
	.byte	0xa6
	.byte	0
	.uleb128 0x20
	.long	0xacb
	.long	.LBB186
	.long	.LBE186
	.byte	0x5
	.byte	0xdd
	.uleb128 0x29
	.long	0xb01
	.long	.LBB187
	.long	.LBE187
	.byte	0x5
	.byte	0xaf
	.long	0xd43
	.uleb128 0x26
	.long	.LVL69
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x30
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xaf8
	.long	.LBB189
	.long	.LBE189
	.byte	0x5
	.byte	0xb0
	.long	0xd71
	.uleb128 0x26
	.long	.LVL70
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x32
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x30
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xaef
	.long	.LBB191
	.long	.LBE191
	.byte	0x5
	.byte	0xb1
	.long	0xd9f
	.uleb128 0x26
	.long	.LVL71
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x33
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x30
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x2
	.byte	0x9
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xae6
	.long	.LBB193
	.long	.LBE193
	.byte	0x5
	.byte	0xb4
	.long	0xdcc
	.uleb128 0x26
	.long	.LVL72
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x35
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x30
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xadd
	.long	.LBB195
	.long	.LBE195
	.byte	0x5
	.byte	0xb5
	.long	0xdf9
	.uleb128 0x26
	.long	.LVL73
	.long	0x8bd
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x36
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x30
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	0xad4
	.long	.LBB197
	.long	.LBE197
	.byte	0x5
	.byte	0xb6
	.uleb128 0x2d
	.long	.LVL74
	.long	0x8bd
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x34
	.long	.LASF127
	.byte	0x5
	.byte	0xbc
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF128
	.byte	0xd
	.byte	0x20
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF129
	.byte	0x3
	.byte	0x84
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF130
	.byte	0xa
	.byte	0x20
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF131
	.byte	0x9
	.byte	0x3a
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF132
	.byte	0x8
	.byte	0x27
	.byte	0x1
	.byte	0x3
	.uleb128 0xe
	.long	.LASF133
	.byte	0x1
	.byte	0x1e
	.byte	0x1
	.byte	0x3
	.long	0xe7b
	.uleb128 0xf
	.long	.LASF46
	.byte	0x1
	.byte	0x1e
	.long	0x36e
	.uleb128 0x14
	.uleb128 0x13
	.long	.LASF55
	.byte	0x1
	.byte	0x20
	.long	0x3b
	.uleb128 0x13
	.long	.LASF56
	.byte	0x1
	.byte	0x20
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF135
	.byte	0x6
	.byte	0x61
	.byte	0x1
	.long	.LFB170
	.long	.LFE170
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x111e
	.uleb128 0x29
	.long	0x4c7
	.long	.LBB243
	.long	.LBE243
	.byte	0x6
	.byte	0x65
	.long	0xeb8
	.uleb128 0x1d
	.long	.LBB244
	.long	.LBE244
	.uleb128 0x37
	.long	0x4d6
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xe4a
	.long	.LBB245
	.long	.LBE245
	.byte	0x6
	.byte	0x6b
	.long	0xf15
	.uleb128 0x38
	.long	0xe57
	.uleb128 0x1d
	.long	.LBB246
	.long	.LBE246
	.uleb128 0x2c
	.long	0xe63
	.long	.LLST32
	.uleb128 0x2c
	.long	0xe6e
	.long	.LLST33
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB247
	.long	.LBE247
	.byte	0x1
	.byte	0x20
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB249
	.long	.LBE249
	.byte	0x1
	.byte	0x20
	.uleb128 0x2a
	.long	0x309
	.long	.LLST34
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0xe4a
	.long	.LBB251
	.long	.LBE251
	.byte	0x6
	.byte	0x6c
	.long	0xf75
	.uleb128 0x38
	.long	0xe57
	.uleb128 0x1d
	.long	.LBB252
	.long	.LBE252
	.uleb128 0x2c
	.long	0xe63
	.long	.LLST35
	.uleb128 0x2c
	.long	0xe6e
	.long	.LLST36
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB253
	.long	.LBE253
	.byte	0x1
	.byte	0x20
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB255
	.long	.LBE255
	.byte	0x1
	.byte	0x20
	.uleb128 0x21
	.long	0x309
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3894
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	0xe41
	.long	.LBB257
	.long	.LBE257
	.byte	0x6
	.byte	0x72
	.uleb128 0x1f
	.long	0xe38
	.long	.LBB259
	.long	.LBE259
	.byte	0x6
	.byte	0x73
	.uleb128 0x1f
	.long	0xe2f
	.long	.LBB261
	.long	.LBE261
	.byte	0x6
	.byte	0x74
	.uleb128 0x29
	.long	0x51b
	.long	.LBB263
	.long	.LBE263
	.byte	0x6
	.byte	0x78
	.long	0xfc8
	.uleb128 0x2a
	.long	0x528
	.long	.LLST37
	.uleb128 0x2a
	.long	0x533
	.long	.LLST38
	.byte	0
	.uleb128 0x29
	.long	0x502
	.long	.LBB265
	.long	.LBE265
	.byte	0x6
	.byte	0x79
	.long	0xfe5
	.uleb128 0x2a
	.long	0x50f
	.long	.LLST39
	.byte	0
	.uleb128 0x1f
	.long	0xe26
	.long	.LBB267
	.long	.LBE267
	.byte	0x6
	.byte	0x7a
	.uleb128 0x1f
	.long	0xe1d
	.long	.LBB269
	.long	.LBE269
	.byte	0x6
	.byte	0x80
	.uleb128 0x1f
	.long	0xe14
	.long	.LBB271
	.long	.LBE271
	.byte	0x6
	.byte	0x81
	.uleb128 0x29
	.long	0x482
	.long	.LBB273
	.long	.LBE273
	.byte	0x6
	.byte	0x84
	.long	0x1093
	.uleb128 0x2a
	.long	0x4a5
	.long	.LLST40
	.uleb128 0x2a
	.long	0x49a
	.long	.LLST41
	.uleb128 0x2a
	.long	0x48f
	.long	.LLST42
	.uleb128 0x1d
	.long	.LBB274
	.long	.LBE274
	.uleb128 0x2c
	.long	0x4b0
	.long	.LLST43
	.uleb128 0x2c
	.long	0x4bb
	.long	.LLST44
	.uleb128 0x29
	.long	0x2b8
	.long	.LBB275
	.long	.LBE275
	.byte	0x9
	.byte	0x2e
	.long	0x1078
	.uleb128 0x2a
	.long	0x2c5
	.long	.LLST45
	.byte	0
	.uleb128 0x20
	.long	0x2b8
	.long	.LBB277
	.long	.LBE277
	.byte	0x9
	.byte	0x2f
	.uleb128 0x2a
	.long	0x2c5
	.long	.LLST46
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x482
	.long	.LBB279
	.long	.LBE279
	.byte	0x6
	.byte	0x85
	.long	0x1114
	.uleb128 0x2a
	.long	0x4a5
	.long	.LLST47
	.uleb128 0x2a
	.long	0x49a
	.long	.LLST48
	.uleb128 0x2a
	.long	0x48f
	.long	.LLST49
	.uleb128 0x1d
	.long	.LBB280
	.long	.LBE280
	.uleb128 0x2c
	.long	0x4b0
	.long	.LLST50
	.uleb128 0x2c
	.long	0x4bb
	.long	.LLST51
	.uleb128 0x29
	.long	0x2b8
	.long	.LBB281
	.long	.LBE281
	.byte	0x9
	.byte	0x2e
	.long	0x10f9
	.uleb128 0x2a
	.long	0x2c5
	.long	.LLST52
	.byte	0
	.uleb128 0x20
	.long	0x2b8
	.long	.LBB283
	.long	.LBE283
	.byte	0x9
	.byte	0x2f
	.uleb128 0x2a
	.long	0x2c5
	.long	.LLST53
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2d
	.long	.LVL84
	.long	0x1888
	.byte	0
	.uleb128 0xe
	.long	.LASF136
	.byte	0xd
	.byte	0x2c
	.byte	0x1
	.byte	0x3
	.long	0x1137
	.uleb128 0xf
	.long	.LASF137
	.byte	0xd
	.byte	0x2c
	.long	0x2d1
	.byte	0
	.uleb128 0xe
	.long	.LASF138
	.byte	0xd
	.byte	0x31
	.byte	0x1
	.byte	0x3
	.long	0x1150
	.uleb128 0xf
	.long	.LASF137
	.byte	0xd
	.byte	0x31
	.long	0x2d1
	.byte	0
	.uleb128 0x39
	.byte	0x1
	.long	.LASF171
	.byte	0x6
	.byte	0x28
	.byte	0x1
	.long	0x58
	.byte	0x1
	.long	.LFB169
	.long	.LFE169
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x1497
	.uleb128 0x3a
	.long	.LBB322
	.long	.LBE322
	.long	0x148d
	.uleb128 0x1e
	.long	.LASF139
	.byte	0x6
	.byte	0x3c
	.long	0x5f
	.long	.LLST54
	.uleb128 0x29
	.long	0x549
	.long	.LBB323
	.long	.LBE323
	.byte	0x6
	.byte	0x30
	.long	0x1210
	.uleb128 0x38
	.long	0x55a
	.uleb128 0x20
	.long	0x328
	.long	.LBB324
	.long	.LBE324
	.byte	0x1
	.byte	0x7d
	.uleb128 0x38
	.long	0x339
	.uleb128 0x1d
	.long	.LBB325
	.long	.LBE325
	.uleb128 0x2c
	.long	0x344
	.long	.LLST55
	.uleb128 0x1d
	.long	.LBB326
	.long	.LBE326
	.uleb128 0x2c
	.long	0x350
	.long	.LLST56
	.uleb128 0x2c
	.long	0x35b
	.long	.LLST57
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB327
	.long	.LBE327
	.byte	0x1
	.byte	0x39
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB329
	.long	.LBE329
	.byte	0x1
	.byte	0x39
	.uleb128 0x2a
	.long	0x309
	.long	.LLST58
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3a
	.long	.LBB331
	.long	.LBE331
	.long	0x1283
	.uleb128 0x1e
	.long	.LASF140
	.byte	0x6
	.byte	0x32
	.long	0x4d
	.long	.LLST59
	.uleb128 0x2e
	.long	.LVL102
	.long	0x1896
	.long	0x1248
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2e
	.long	.LVL105
	.long	0x61a
	.long	0x1264
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.uleb128 0x26
	.long	.LVL106
	.long	0x61a
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x27
	.byte	0x1
	.byte	0x66
	.byte	0x2
	.byte	0x8c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x328
	.long	.LBB332
	.long	.LBE332
	.byte	0x6
	.byte	0x3c
	.long	0x12f3
	.uleb128 0x38
	.long	0x339
	.uleb128 0x1d
	.long	.LBB333
	.long	.LBE333
	.uleb128 0x2c
	.long	0x344
	.long	.LLST60
	.uleb128 0x1d
	.long	.LBB334
	.long	.LBE334
	.uleb128 0x2c
	.long	0x350
	.long	.LLST61
	.uleb128 0x2c
	.long	0x35b
	.long	.LLST62
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB335
	.long	.LBE335
	.byte	0x1
	.byte	0x39
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB337
	.long	.LBE337
	.byte	0x1
	.byte	0x39
	.uleb128 0x2a
	.long	0x309
	.long	.LLST63
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x111e
	.long	.LBB339
	.long	.LBE339
	.byte	0x6
	.byte	0x42
	.long	0x1310
	.uleb128 0x2a
	.long	0x112b
	.long	.LLST64
	.byte	0
	.uleb128 0x29
	.long	0x1137
	.long	.LBB341
	.long	.LBE341
	.byte	0x6
	.byte	0x4c
	.long	0x132d
	.uleb128 0x2a
	.long	0x1144
	.long	.LLST65
	.byte	0
	.uleb128 0x29
	.long	0x1137
	.long	.LBB343
	.long	.LBE343
	.byte	0x6
	.byte	0x50
	.long	0x134a
	.uleb128 0x2a
	.long	0x1144
	.long	.LLST66
	.byte	0
	.uleb128 0x29
	.long	0x566
	.long	.LBB345
	.long	.LBE345
	.byte	0x6
	.byte	0x54
	.long	0x13d9
	.uleb128 0x38
	.long	0x577
	.uleb128 0x20
	.long	0x328
	.long	.LBB346
	.long	.LBE346
	.byte	0x1
	.byte	0x8e
	.uleb128 0x21
	.long	0x339
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1d
	.long	.LBB347
	.long	.LBE347
	.uleb128 0x2c
	.long	0x344
	.long	.LLST67
	.uleb128 0x1d
	.long	.LBB348
	.long	.LBE348
	.uleb128 0x2c
	.long	0x350
	.long	.LLST68
	.uleb128 0x2c
	.long	0x35b
	.long	.LLST69
	.uleb128 0x1f
	.long	0x31b
	.long	.LBB349
	.long	.LBE349
	.byte	0x1
	.byte	0x39
	.uleb128 0x20
	.long	0x2fc
	.long	.LBB351
	.long	.LBE351
	.byte	0x1
	.byte	0x39
	.uleb128 0x21
	.long	0x309
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+5016
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x29
	.long	0x4e4
	.long	.LBB353
	.long	.LBE353
	.byte	0x6
	.byte	0x55
	.long	0x13f6
	.uleb128 0x2a
	.long	0x4f1
	.long	.LLST70
	.byte	0
	.uleb128 0x29
	.long	0x111e
	.long	.LBB355
	.long	.LBE355
	.byte	0x6
	.byte	0x57
	.long	0x1413
	.uleb128 0x2a
	.long	0x112b
	.long	.LLST71
	.byte	0
	.uleb128 0x2e
	.long	.LVL114
	.long	0x6a3
	.long	0x142f
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.uleb128 0x2e
	.long	.LVL115
	.long	0x18a4
	.long	0x144b
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2e
	.long	.LVL126
	.long	0x6a3
	.long	0x1467
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.uleb128 0x2e
	.long	.LVL129
	.long	0x18b1
	.long	0x1483
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2d
	.long	.LVL130
	.long	0x18be
	.byte	0
	.uleb128 0x2d
	.long	.LVL96
	.long	0xe7b
	.byte	0
	.uleb128 0x3b
	.long	.LASF141
	.byte	0x3
	.word	0x113
	.byte	0x1
	.byte	0x1
	.byte	0x3
	.uleb128 0x3c
	.long	.LASF142
	.byte	0x3
	.word	0x107
	.byte	0x1
	.byte	0x3
	.uleb128 0x34
	.long	.LASF143
	.byte	0x3
	.byte	0xa7
	.byte	0x1
	.byte	0x3
	.uleb128 0x3d
	.byte	0x1
	.long	.LASF145
	.byte	0x6
	.byte	0x95
	.byte	0x1
	.byte	0x1
	.long	.LFB171
	.long	.LFE171
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x1697
	.uleb128 0x29
	.long	0x14a2
	.long	.LBB368
	.long	.LBE368
	.byte	0x6
	.byte	0x97
	.long	0x152d
	.uleb128 0x2e
	.long	.LVL131
	.long	0x730
	.long	0x14f7
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x2e
	.long	.LVL132
	.long	0x76e
	.long	0x151c
	.uleb128 0x27
	.byte	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x3
	.byte	0xa
	.word	0xe79e
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x40
	.byte	0
	.uleb128 0x26
	.long	.LVL133
	.long	0x730
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	0x1497
	.long	.LBB370
	.long	.LBE370
	.byte	0x6
	.byte	0x98
	.uleb128 0x3e
	.long	0x14ac
	.long	.LBB371
	.long	.LBE371
	.byte	0x3
	.word	0x115
	.long	0x1575
	.uleb128 0x2e
	.long	.LVL134
	.long	0x730
	.long	0x1564
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x26
	.long	.LVL135
	.long	0x730
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0x3f
	.long	0x3a2
	.long	.LBB373
	.long	.LBE373
	.byte	0x3
	.word	0x116
	.uleb128 0x40
	.long	0x3b3
	.byte	0
	.uleb128 0x40
	.long	0x3be
	.byte	0x4
	.uleb128 0x40
	.long	0x3c9
	.byte	0
	.uleb128 0x40
	.long	0x3d4
	.byte	0
	.uleb128 0x1d
	.long	.LBB374
	.long	.LBE374
	.uleb128 0x2c
	.long	0x3df
	.long	.LLST72
	.uleb128 0x2c
	.long	0x3ea
	.long	.LLST73
	.uleb128 0x41
	.long	0x3f5
	.byte	0
	.uleb128 0x2c
	.long	0x400
	.long	.LLST74
	.uleb128 0x42
	.long	0x583
	.long	.LBB375
	.long	.Ldebug_ranges0+0x18
	.byte	0x3
	.byte	0xf2
	.long	0x1611
	.uleb128 0x2a
	.long	0x594
	.long	.LLST75
	.uleb128 0x43
	.long	.Ldebug_ranges0+0x18
	.uleb128 0x2c
	.long	0x59f
	.long	.LLST76
	.uleb128 0x43
	.long	.Ldebug_ranges0+0x30
	.uleb128 0x2c
	.long	0x5ab
	.long	.LLST77
	.uleb128 0x26
	.long	.LVL146
	.long	0x730
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2e
	.long	.LVL136
	.long	0xa3b
	.long	0x162f
	.uleb128 0x27
	.byte	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x1
	.byte	0x30
	.byte	0
	.uleb128 0x2e
	.long	.LVL137
	.long	0xa3b
	.long	0x164d
	.uleb128 0x27
	.byte	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x1
	.byte	0x34
	.byte	0
	.uleb128 0x2e
	.long	.LVL141
	.long	0x76e
	.long	0x1671
	.uleb128 0x27
	.byte	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x27
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.byte	0x38
	.byte	0
	.uleb128 0x2e
	.long	.LVL142
	.long	0x730
	.long	0x1684
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0x26
	.long	.LVL149
	.long	0x730
	.uleb128 0x27
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF146
	.byte	0x6
	.byte	0xa8
	.byte	0x1
	.long	.LFB172
	.long	.LFE172
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x16cb
	.uleb128 0x44
	.long	.LVL150
	.byte	0x1
	.long	0x18cb
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF147
	.byte	0x6
	.byte	0xae
	.byte	0x1
	.long	.LFB173
	.long	.LFE173
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x16ff
	.uleb128 0x44
	.long	.LVL151
	.byte	0x1
	.long	0x18d8
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x35
	.byte	0x1
	.long	.LASF148
	.byte	0x6
	.byte	0xb8
	.byte	0x1
	.long	.LFB174
	.long	.LFE174
	.long	.LLST78
	.byte	0x1
	.long	0x1742
	.uleb128 0x1b
	.long	.LASF149
	.byte	0x6
	.byte	0xb8
	.long	0x1748
	.long	.LLST79
	.uleb128 0x1d
	.long	.LBB381
	.long	.LBE381
	.uleb128 0x1e
	.long	.LASF150
	.byte	0x6
	.byte	0xc2
	.long	0x3b
	.long	.LLST80
	.byte	0
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x249
	.uleb128 0x9
	.long	0x1742
	.uleb128 0x45
	.long	.LASF172
	.byte	0xe
	.byte	0x13
	.byte	0x3
	.long	0x1765
	.uleb128 0x14
	.uleb128 0x15
	.string	"i"
	.byte	0xe
	.byte	0x15
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0x35
	.byte	0x1
	.long	.LASF151
	.byte	0x6
	.byte	0xe3
	.byte	0x1
	.long	.LFB175
	.long	.LFE175
	.long	.LLST81
	.byte	0x1
	.long	0x17d9
	.uleb128 0x1b
	.long	.LASF149
	.byte	0x6
	.byte	0xe3
	.long	0x1748
	.long	.LLST82
	.uleb128 0x1e
	.long	.LASF152
	.byte	0x6
	.byte	0xe5
	.long	0x18d
	.long	.LLST83
	.uleb128 0x20
	.long	0x174d
	.long	.LBB385
	.long	.LBE385
	.byte	0x6
	.byte	0xe9
	.uleb128 0x1d
	.long	.LBB386
	.long	.LBE386
	.uleb128 0x2c
	.long	0x175a
	.long	.LLST84
	.uleb128 0x26
	.long	.LVL170
	.long	0x18a4
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x35
	.byte	0x1
	.long	.LASF153
	.byte	0x6
	.byte	0xf6
	.byte	0x1
	.long	.LFB176
	.long	.LFE176
	.long	.LLST85
	.byte	0x1
	.long	0x180c
	.uleb128 0x26
	.long	.LVL174
	.long	0x61a
	.uleb128 0x27
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.byte	0
	.uleb128 0x46
	.long	.LASF154
	.byte	0xd
	.byte	0x1b
	.long	0x3b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	TxLEDPulse
	.uleb128 0x46
	.long	.LASF155
	.byte	0xd
	.byte	0x1c
	.long	0x3b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	RxLEDPulse
	.uleb128 0xb
	.long	0xf1
	.long	0x1840
	.uleb128 0xc
	.long	0x98
	.byte	0x3f
	.byte	0
	.uleb128 0x46
	.long	.LASF156
	.byte	0xe
	.byte	0xc
	.long	0x1830
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	command
	.uleb128 0x46
	.long	.LASF157
	.byte	0x6
	.byte	0x11
	.long	0x249
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.uleb128 0x46
	.long	.LASF158
	.byte	0x6
	.byte	0x9
	.long	0x2ad
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.uleb128 0x46
	.long	.LASF159
	.byte	0x6
	.byte	0xa
	.long	0x2ad
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x47
	.byte	0x1
	.byte	0x1
	.long	.LASF160
	.long	.LASF160
	.byte	0x13
	.word	0x10c
	.uleb128 0x47
	.byte	0x1
	.byte	0x1
	.long	.LASF161
	.long	.LASF161
	.byte	0x11
	.word	0x10a
	.uleb128 0x48
	.byte	0x1
	.byte	0x1
	.long	.LASF162
	.long	.LASF162
	.byte	0x11
	.byte	0xed
	.uleb128 0x48
	.byte	0x1
	.byte	0x1
	.long	.LASF163
	.long	.LASF163
	.byte	0x11
	.byte	0xb0
	.uleb128 0x48
	.byte	0x1
	.byte	0x1
	.long	.LASF164
	.long	.LASF164
	.byte	0x14
	.byte	0xb3
	.uleb128 0x48
	.byte	0x1
	.byte	0x1
	.long	.LASF165
	.long	.LASF165
	.byte	0x11
	.byte	0xa2
	.uleb128 0x48
	.byte	0x1
	.byte	0x1
	.long	.LASF166
	.long	.LASF166
	.byte	0x11
	.byte	0xa9
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x45
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x47
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x48
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL3
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL3
	.long	.LFE104
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL1
	.long	.LVL5
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST2:
	.long	.LVL2
	.long	.LVL4
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL4
	.long	.LFE104
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL6
	.long	.LVL12
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL12
	.long	.LFE105
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL8
	.long	.LVL11
	.word	0x1
	.byte	0x65
	.long	0
	.long	0
.LLST5:
	.long	.LVL9
	.long	.LVL10
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL10
	.long	.LFE105
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LVL13
	.long	.LVL14
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL14
	.long	.LFE118
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST7:
	.long	.LFB120
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI7
	.long	.LFE120
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	0
	.long	0
.LLST8:
	.long	.LVL16
	.long	.LVL18
	.word	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL18
	.long	.LVL23
	.word	0xc
	.byte	0x5c
	.byte	0x93
	.uleb128 0x1
	.byte	0x5d
	.byte	0x93
	.uleb128 0x1
	.byte	0x5e
	.byte	0x93
	.uleb128 0x1
	.byte	0x5f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL23
	.long	.LFE120
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL16
	.long	.LVL18
	.word	0x1
	.byte	0x64
	.long	.LVL18
	.long	.LVL22
	.word	0x1
	.byte	0x60
	.long	.LVL22
	.long	.LFE120
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x9f
	.long	0
	.long	0
.LLST10:
	.long	.LVL17
	.long	.LVL18
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL18
	.long	.LVL19
	.word	0x1
	.byte	0x6c
	.long	.LVL19
	.long	.LVL20
	.word	0x3
	.byte	0x8c
	.sleb128 1
	.byte	0x9f
	.long	.LVL20
	.long	.LVL21
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST11:
	.long	.LVL24
	.long	.LVL28
	.word	0x1
	.byte	0x68
	.long	.LVL28
	.long	.LFE135
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST12:
	.long	.LVL28
	.long	.LVL29
	.word	0x9
	.byte	0x88
	.sleb128 0
	.byte	0x32
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x30
	.byte	0x2e
	.byte	0x9f
	.long	0
	.long	0
.LLST13:
	.long	.LVL24
	.long	.LVL25
	.word	0x2
	.byte	0x37
	.byte	0x9f
	.long	.LVL25
	.long	.LVL26
	.word	0x1
	.byte	0x62
	.long	.LVL26
	.long	.LVL27
	.word	0x3
	.byte	0x82
	.sleb128 -1
	.byte	0x9f
	.long	.LVL27
	.long	.LFE135
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST14:
	.long	.LFB139
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI11
	.long	.LFE139
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	0
	.long	0
.LLST15:
	.long	.LVL30
	.long	.LVL32-1
	.word	0x1
	.byte	0x68
	.long	.LVL32-1
	.long	.LVL51
	.word	0x1
	.byte	0x61
	.long	.LVL51
	.long	.LFE139
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST16:
	.long	.LVL30
	.long	.LVL32-1
	.word	0x1
	.byte	0x66
	.long	.LVL32-1
	.long	.LVL52
	.word	0x1
	.byte	0x60
	.long	.LVL52
	.long	.LFE139
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST17:
	.long	.LVL30
	.long	.LVL32-1
	.word	0x1
	.byte	0x64
	.long	.LVL32-1
	.long	.LVL49
	.word	0x1
	.byte	0x6d
	.long	.LVL49
	.long	.LFE139
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x9f
	.long	0
	.long	0
.LLST18:
	.long	.LVL31
	.long	.LVL32-1
	.word	0x1
	.byte	0x68
	.long	.LVL32-1
	.long	.LVL43
	.word	0x1
	.byte	0x61
	.long	0
	.long	0
.LLST19:
	.long	.LVL36
	.long	.LVL38
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL38
	.long	.LVL42
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST20:
	.long	.LVL37
	.long	.LVL38
	.word	0x2
	.byte	0x37
	.byte	0x9f
	.long	.LVL38
	.long	.LVL40
	.word	0x1
	.byte	0x62
	.long	.LVL40
	.long	.LVL41
	.word	0x3
	.byte	0x82
	.sleb128 -1
	.byte	0x9f
	.long	.LVL41
	.long	.LVL42
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST21:
	.long	.LVL43
	.long	.LVL47
	.word	0xa
	.byte	0x8d
	.sleb128 0
	.byte	0x20
	.byte	0x8c
	.sleb128 0
	.byte	0x1a
	.byte	0x80
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.long	.LVL47
	.long	.LVL48-1
	.word	0x1
	.byte	0x68
	.long	.LVL48-1
	.long	.LVL49
	.word	0xa
	.byte	0x8d
	.sleb128 0
	.byte	0x20
	.byte	0x8c
	.sleb128 0
	.byte	0x1a
	.byte	0x80
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.long	.LVL49
	.long	.LVL50
	.word	0xb
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x20
	.byte	0x8c
	.sleb128 0
	.byte	0x1a
	.byte	0x80
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL43
	.long	.LVL51
	.word	0x1
	.byte	0x61
	.long	.LVL51
	.long	.LFE139
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST23:
	.long	.LFB115
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI15
	.long	.LFE115
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	0
	.long	0
.LLST24:
	.long	.LVL54
	.long	.LVL58
	.word	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL58
	.long	.LFE115
	.word	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST25:
	.long	.LVL55
	.long	.LVL56
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL56
	.long	.LFE115
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST26:
	.long	.LFB163
	.long	.LCFI16
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI16
	.long	.LCFI17
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI17
	.long	.LFE163
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST27:
	.long	.LFB164
	.long	.LCFI18
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI18
	.long	.LCFI19
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI19
	.long	.LCFI20
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI20
	.long	.LCFI21
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI21
	.long	.LCFI22
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI22
	.long	.LCFI23
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI23
	.long	.LCFI24
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI24
	.long	.LCFI25
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI25
	.long	.LCFI26
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI26
	.long	.LCFI27
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	.LCFI27
	.long	.LCFI28
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 12
	.long	.LCFI28
	.long	.LCFI29
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 13
	.long	.LCFI29
	.long	.LCFI30
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 14
	.long	.LCFI30
	.long	.LCFI31
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 15
	.long	.LCFI31
	.long	.LFE164
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 16
	.long	0
	.long	0
.LLST28:
	.long	.LVL59
	.long	.LVL60
	.word	0x6
	.byte	0x9e
	.uleb128 0x4
	.long	0x40533333
	.long	0
	.long	0
.LLST29:
	.long	.LVL60
	.long	.LVL61
	.word	0x6
	.byte	0x9e
	.uleb128 0x4
	.long	0x40666666
	.long	0
	.long	0
.LLST30:
	.long	.LVL61
	.long	.LVL62
	.word	0x6
	.byte	0x9e
	.uleb128 0x4
	.long	0x4079999a
	.long	0
	.long	0
.LLST31:
	.long	.LVL62
	.long	.LVL63
	.word	0x6
	.byte	0x9e
	.uleb128 0x4
	.long	0x3f8ccccd
	.long	0
	.long	0
.LLST32:
	.long	.LVL76
	.long	.LVL79
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST33:
	.long	.LVL77
	.long	.LVL78
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL78
	.long	.LVL79
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST34:
	.long	.LVL78
	.long	.LVL82
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3801
	.sleb128 0
	.long	.LVL82
	.long	.LFE170
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3894
	.sleb128 0
	.long	0
	.long	0
.LLST35:
	.long	.LVL80
	.long	.LVL83
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST36:
	.long	.LVL81
	.long	.LVL82
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL82
	.long	.LVL83
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST37:
	.long	.LVL84
	.long	.LVL85
	.word	0x4
	.byte	0xa
	.word	0x2580
	.byte	0x9f
	.long	0
	.long	0
.LLST38:
	.long	.LVL84
	.long	.LVL85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST39:
	.long	.LVL85
	.long	.LVL86
	.word	0x3
	.byte	0x8
	.byte	0x5c
	.byte	0x9f
	.long	0
	.long	0
.LLST40:
	.long	.LVL87
	.long	.LVL91
	.word	0x4
	.byte	0xa
	.word	0x2ee
	.byte	0x9f
	.long	0
	.long	0
.LLST41:
	.long	.LVL87
	.long	.LVL91
	.word	0x2
	.byte	0x32
	.byte	0x9f
	.long	0
	.long	0
.LLST42:
	.long	.LVL87
	.long	.LVL91
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST43:
	.long	.LVL87
	.long	.LVL91
	.word	0x4
	.byte	0xa
	.word	0x3a2
	.byte	0x9f
	.long	0
	.long	0
.LLST44:
	.long	.LVL87
	.long	.LVL91
	.word	0x4
	.byte	0xa
	.word	0x23a2
	.byte	0x9f
	.long	0
	.long	0
.LLST45:
	.long	.LVL88
	.long	.LVL89
	.word	0x3
	.byte	0x8
	.byte	0x23
	.byte	0x9f
	.long	0
	.long	0
.LLST46:
	.long	.LVL89
	.long	.LVL90
	.word	0x3
	.byte	0x9
	.byte	0xa2
	.byte	0x9f
	.long	0
	.long	0
.LLST47:
	.long	.LVL91
	.long	.LVL95
	.word	0x4
	.byte	0xa
	.word	0x4e2
	.byte	0x9f
	.long	0
	.long	0
.LLST48:
	.long	.LVL91
	.long	.LVL95
	.word	0x2
	.byte	0x33
	.byte	0x9f
	.long	0
	.long	0
.LLST49:
	.long	.LVL91
	.long	.LVL95
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST50:
	.long	.LVL91
	.long	.LVL95
	.word	0x4
	.byte	0xa
	.word	0x60f
	.byte	0x9f
	.long	0
	.long	0
.LLST51:
	.long	.LVL91
	.long	.LVL95
	.word	0x4
	.byte	0xa
	.word	0x360f
	.byte	0x9f
	.long	0
	.long	0
.LLST52:
	.long	.LVL92
	.long	.LVL93
	.word	0x3
	.byte	0x8
	.byte	0x36
	.byte	0x9f
	.long	0
	.long	0
.LLST53:
	.long	.LVL93
	.long	.LVL94
	.word	0x2
	.byte	0x3f
	.byte	0x9f
	.long	0
	.long	0
.LLST54:
	.long	.LVL113
	.long	.LVL116
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	.LVL116
	.long	.LVL117
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL117
	.long	.LVL121
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	0
	.long	0
.LLST55:
	.long	.LVL100
	.long	.LVL101
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST56:
	.long	.LVL98
	.long	.LVL101
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST57:
	.long	.LVL99
	.long	.LVL100
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL100
	.long	.LVL101
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST58:
	.long	.LVL100
	.long	.LVL109
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+4562
	.sleb128 0
	.long	.LVL109
	.long	.LVL124
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+4790
	.sleb128 0
	.long	.LVL124
	.long	.LFE169
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+5016
	.sleb128 0
	.long	0
	.long	0
.LLST59:
	.long	.LVL103
	.long	.LVL104
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL104
	.long	.LVL106
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST60:
	.long	.LVL109
	.long	.LVL110
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST61:
	.long	.LVL107
	.long	.LVL110
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST62:
	.long	.LVL108
	.long	.LVL109
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL109
	.long	.LVL110
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST63:
	.long	.LVL109
	.long	.LVL124
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+4790
	.sleb128 0
	.long	.LVL124
	.long	.LFE169
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+5016
	.sleb128 0
	.long	0
	.long	0
.LLST64:
	.long	.LVL111
	.long	.LVL112
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST65:
	.long	.LVL118
	.long	.LVL119
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST66:
	.long	.LVL120
	.long	.LVL121
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST67:
	.long	.LVL124
	.long	.LVL125
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST68:
	.long	.LVL122
	.long	.LVL125
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST69:
	.long	.LVL123
	.long	.LVL124
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL124
	.long	.LVL125
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST70:
	.long	.LVL126
	.long	.LVL127
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST71:
	.long	.LVL127
	.long	.LVL128
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST72:
	.long	.LVL139
	.long	.LVL140
	.word	0x1
	.byte	0x68
	.long	.LVL140
	.long	.LFE171
	.word	0x1
	.byte	0x5c
	.long	0
	.long	0
.LLST73:
	.long	.LVL139
	.long	.LVL140
	.word	0x2
	.byte	0x32
	.byte	0x9f
	.long	.LVL148
	.long	.LFE171
	.word	0x1
	.byte	0x58
	.long	0
	.long	0
.LLST74:
	.long	.LVL137
	.long	.LVL138
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST75:
	.long	.LVL142
	.long	.LVL148
	.word	0x2
	.byte	0x33
	.byte	0x9f
	.long	0
	.long	0
.LLST76:
	.long	.LVL142
	.long	.LVL144
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL144
	.long	.LVL148
	.word	0xc
	.byte	0x58
	.byte	0x93
	.uleb128 0x1
	.byte	0x59
	.byte	0x93
	.uleb128 0x1
	.byte	0x5a
	.byte	0x93
	.uleb128 0x1
	.byte	0x5b
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST77:
	.long	.LVL143
	.long	.LVL144
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL144
	.long	.LVL146
	.word	0x1
	.byte	0x6c
	.long	.LVL146
	.long	.LVL147
	.word	0x3
	.byte	0x8c
	.sleb128 1
	.byte	0x9f
	.long	.LVL147
	.long	.LVL148
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST78:
	.long	.LFB174
	.long	.LCFI32
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI32
	.long	.LCFI33
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI33
	.long	.LFE174
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST79:
	.long	.LVL152
	.long	.LVL153
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL153
	.long	.LVL164
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL164
	.long	.LFE174
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST80:
	.long	.LVL154
	.long	.LVL155
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL155
	.long	.LVL156
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	.LVL156
	.long	.LVL157
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL157
	.long	.LVL162
	.word	0x1
	.byte	0x68
	.long	.LVL162
	.long	.LVL163
	.word	0x2
	.byte	0x8
	.byte	0xca
	.long	0
	.long	0
.LLST81:
	.long	.LFB175
	.long	.LCFI34
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI34
	.long	.LCFI35
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI35
	.long	.LFE175
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST82:
	.long	.LVL165
	.long	.LVL167
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL167
	.long	.LVL168
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL168
	.long	.LVL172
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	.LVL172
	.long	.LVL173
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL173
	.long	.LFE175
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST83:
	.long	.LVL166
	.long	.LVL167
	.word	0x7
	.byte	0x88
	.sleb128 13
	.byte	0x94
	.byte	0x1
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	.LVL167
	.long	.LVL168
	.word	0x5
	.byte	0x88
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	.LVL172
	.long	.LVL173
	.word	0x5
	.byte	0x88
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
.LLST84:
	.long	.LVL168
	.long	.LVL169
	.word	0x9
	.byte	0x8c
	.sleb128 0
	.byte	0x3
	.long	.LC0
	.byte	0x1c
	.byte	0x9f
	.long	.LVL169
	.long	.LVL170
	.word	0xa
	.byte	0x3
	.long	.LC0
	.byte	0x20
	.byte	0x8c
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.long	.LVL170
	.long	.LVL171
	.word	0x9
	.byte	0x8c
	.sleb128 0
	.byte	0x3
	.long	.LC0
	.byte	0x1c
	.byte	0x9f
	.long	0
	.long	0
.LLST85:
	.long	.LFB176
	.long	.LCFI36
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI36
	.long	.LCFI37
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI37
	.long	.LCFI38
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI38
	.long	.LCFI39
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI39
	.long	.LCFI40
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI40
	.long	.LCFI41
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI41
	.long	.LCFI42
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI42
	.long	.LCFI43
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI43
	.long	.LCFI44
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI44
	.long	.LCFI45
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	.LCFI45
	.long	.LCFI46
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 12
	.long	.LCFI46
	.long	.LCFI47
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 13
	.long	.LCFI47
	.long	.LCFI48
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 14
	.long	.LCFI48
	.long	.LCFI49
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 15
	.long	.LCFI49
	.long	.LFE176
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 16
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0xac
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB104
	.long	.LFE104-.LFB104
	.long	.LFB105
	.long	.LFE105-.LFB105
	.long	.LFB118
	.long	.LFE118-.LFB118
	.long	.LFB120
	.long	.LFE120-.LFB120
	.long	.LFB133
	.long	.LFE133-.LFB133
	.long	.LFB134
	.long	.LFE134-.LFB134
	.long	.LFB135
	.long	.LFE135-.LFB135
	.long	.LFB139
	.long	.LFE139-.LFB139
	.long	.LFB115
	.long	.LFE115-.LFB115
	.long	.LFB163
	.long	.LFE163-.LFB163
	.long	.LFB164
	.long	.LFE164-.LFB164
	.long	.LFB170
	.long	.LFE170-.LFB170
	.long	.LFB169
	.long	.LFE169-.LFB169
	.long	.LFB171
	.long	.LFE171-.LFB171
	.long	.LFB172
	.long	.LFE172-.LFB172
	.long	.LFB173
	.long	.LFE173-.LFB173
	.long	.LFB174
	.long	.LFE174-.LFB174
	.long	.LFB175
	.long	.LFE175-.LFB175
	.long	.LFB176
	.long	.LFE176-.LFB176
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LBB117
	.long	.LBE117
	.long	.LBB120
	.long	.LBE120
	.long	0
	.long	0
	.long	.LBB375
	.long	.LBE375
	.long	.LBB380
	.long	.LBE380
	.long	0
	.long	0
	.long	.LBB377
	.long	.LBE377
	.long	.LBB378
	.long	.LBE378
	.long	0
	.long	0
	.long	.LFB104
	.long	.LFE104
	.long	.LFB105
	.long	.LFE105
	.long	.LFB118
	.long	.LFE118
	.long	.LFB120
	.long	.LFE120
	.long	.LFB133
	.long	.LFE133
	.long	.LFB134
	.long	.LFE134
	.long	.LFB135
	.long	.LFE135
	.long	.LFB139
	.long	.LFE139
	.long	.LFB115
	.long	.LFE115
	.long	.LFB163
	.long	.LFE163
	.long	.LFB164
	.long	.LFE164
	.long	.LFB170
	.long	.LFE170
	.long	.LFB169
	.long	.LFE169
	.long	.LFB171
	.long	.LFE171
	.long	.LFB172
	.long	.LFE172
	.long	.LFB173
	.long	.LFE173
	.long	.LFB174
	.long	.LFE174
	.long	.LFB175
	.long	.LFE175
	.long	.LFB176
	.long	.LFE176
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF67:
	.string	"request"
.LASF92:
	.string	"_bits"
.LASF87:
	.string	"BaudRate"
.LASF60:
	.string	"_feedback_ratio"
.LASF79:
	.string	"_command"
.LASF146:
	.string	"EVENT_USB_Device_ConfigurationChanged"
.LASF150:
	.string	"ConfigMask"
.LASF42:
	.string	"LineEncoding"
.LASF108:
	.string	"_subaddress"
.LASF167:
	.string	"GNU C99 5.4.0 -mn-flash=1 -mno-skip-bug -mmcu=avr35 -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing"
.LASF22:
	.string	"CDC_PARITY_Space"
.LASF111:
	.string	"PM_UpdateReg"
.LASF158:
	.string	"USBtoUSART_Buffer"
.LASF6:
	.string	"unsigned int"
.LASF37:
	.string	"BaudRateBPS"
.LASF84:
	.string	"SPI_Init"
.LASF135:
	.string	"SetupHardware"
.LASF128:
	.string	"LEDs_Init"
.LASF49:
	.string	"SPI_SendByte"
.LASF129:
	.string	"SW_Init"
.LASF133:
	.string	"RingBuffer_InitBuffer"
.LASF40:
	.string	"DataBits"
.LASF44:
	.string	"State"
.LASF100:
	.string	"SW_PulseClock"
.LASF27:
	.string	"DataINEndpointDoubleBank"
.LASF149:
	.string	"CDCInterfaceInfo"
.LASF25:
	.string	"DataINEndpointNumber"
.LASF141:
	.string	"SW_Connect"
.LASF170:
	.string	"__vector_9"
.LASF104:
	.string	"I2C_EndTransmission"
.LASF73:
	.string	"SW_WriteMem"
.LASF8:
	.string	"uint32_t"
.LASF0:
	.string	"int8_t"
.LASF30:
	.string	"DataOUTEndpointDoubleBank"
.LASF58:
	.string	"PM_Calculate_DVBx"
.LASF136:
	.string	"LEDs_TurnOnLEDs"
.LASF64:
	.string	"_RnW"
.LASF169:
	.string	"/nethome/mchang87/Projects/RRAM/atmega16u2/ArduinoCore-avr/firmwares/atmegaxxu2/rram-usbserial"
.LASF147:
	.string	"EVENT_USB_Device_UnhandledControlRequest"
.LASF28:
	.string	"DataOUTEndpointNumber"
.LASF75:
	.string	"_chip_mask"
.LASF32:
	.string	"NotificationEndpointSize"
.LASF74:
	.string	"DAC_Configure_DAC"
.LASF131:
	.string	"DAC_Grasp"
.LASF33:
	.string	"NotificationEndpointDoubleBank"
.LASF4:
	.string	"int16_t"
.LASF93:
	.string	"result"
.LASF11:
	.string	"long long unsigned int"
.LASF71:
	.string	"_address"
.LASF94:
	.string	"PM_Adjust_3V3"
.LASF145:
	.string	"Write_Program"
.LASF143:
	.string	"SW_LineReset"
.LASF16:
	.string	"CDC_LineEncodingFormats_t"
.LASF126:
	.string	"PM_Disable_3V3"
.LASF76:
	.string	"_target"
.LASF113:
	.string	"PM_PowerUp"
.LASF43:
	.string	"Config"
.LASF31:
	.string	"NotificationEndpointNumber"
.LASF78:
	.string	"value"
.LASF36:
	.string	"DeviceToHost"
.LASF161:
	.string	"CDC_Device_ReceiveByte"
.LASF106:
	.string	"I2C_SendByte"
.LASF65:
	.string	"_reg"
.LASF107:
	.string	"PM_WriteReg"
.LASF50:
	.string	"Dataflash_SendByte"
.LASF86:
	.string	"Serial_Init"
.LASF34:
	.string	"_Bool"
.LASF122:
	.string	"PM_Disable_AVDD_SRAM"
.LASF51:
	.string	"Byte"
.LASF124:
	.string	"PM_Disable_AVDD_WL"
.LASF127:
	.string	"PM_Init"
.LASF125:
	.string	"PM_Disable_AVDD_WR"
.LASF88:
	.string	"DoubleSpeed"
.LASF90:
	.string	"RingBuffer_IsEmpty"
.LASF47:
	.string	"Count"
.LASF29:
	.string	"DataOUTEndpointSize"
.LASF99:
	.string	"RingBuffer_Insert"
.LASF23:
	.string	"char"
.LASF118:
	.string	"PM_Enable_AVDD_SRAM"
.LASF103:
	.string	"I2C_StartTransmission"
.LASF68:
	.string	"data"
.LASF1:
	.string	"uint8_t"
.LASF70:
	.string	"SW_ReadMem"
.LASF159:
	.string	"USARTtoUSB_Buffer"
.LASF83:
	.string	"DataByte"
.LASF172:
	.string	"UARTConsole_PrintHeader"
.LASF53:
	.string	"SPI_ReceiveByte"
.LASF155:
	.string	"RxLEDPulse"
.LASF160:
	.string	"USB_Init"
.LASF35:
	.string	"HostToDevice"
.LASF164:
	.string	"USB_USBTask"
.LASF10:
	.string	"long long int"
.LASF97:
	.string	"PM_Adjust_AVDD_RRAM"
.LASF52:
	.string	"__iRestore"
.LASF130:
	.string	"RRAM_Grasp"
.LASF57:
	.string	"RingBuffer_GetCount"
.LASF137:
	.string	"LEDMask"
.LASF110:
	.string	"I2C_ReceiveByte"
.LASF138:
	.string	"LEDs_TurnOffLEDs"
.LASF91:
	.string	"SW_Receive"
.LASF24:
	.string	"ControlInterfaceNumber"
.LASF156:
	.string	"command"
.LASF116:
	.string	"PM_Enable_3V3"
.LASF81:
	.string	"temp_reg"
.LASF163:
	.string	"CDC_Device_USBTask"
.LASF13:
	.string	"CDC_LINEENCODING_OneStopBit"
.LASF19:
	.string	"CDC_PARITY_Odd"
.LASF55:
	.string	"sreg_save"
.LASF5:
	.string	"uint16_t"
.LASF102:
	.string	"SW_Send"
.LASF48:
	.string	"RingBuff_t"
.LASF89:
	.string	"RingBuffer_IsFull"
.LASF69:
	.string	"parity"
.LASF120:
	.string	"PM_PowerDown"
.LASF63:
	.string	"_APnDP"
.LASF46:
	.string	"Buffer"
.LASF7:
	.string	"long int"
.LASF157:
	.string	"VirtualSerial_CDC_Interface"
.LASF26:
	.string	"DataINEndpointSize"
.LASF152:
	.string	"DataTerminalReady"
.LASF144:
	.string	"getParity"
.LASF142:
	.string	"SW_JTAGToSW"
.LASF66:
	.string	"_data"
.LASF132:
	.string	"Dataflash_Grasp"
.LASF105:
	.string	"RingBuffer_Remove"
.LASF139:
	.string	"BufferCount"
.LASF62:
	.string	"SW_SendPacket"
.LASF18:
	.string	"CDC_PARITY_None"
.LASF20:
	.string	"CDC_PARITY_Even"
.LASF82:
	.string	"Serial_TxByte"
.LASF85:
	.string	"SPIOptions"
.LASF166:
	.string	"CDC_Device_ProcessControlRequest"
.LASF121:
	.string	"PM_Disable_AVDD_RRAM"
.LASF59:
	.string	"_target_voltage"
.LASF12:
	.string	"sizetype"
.LASF9:
	.string	"long unsigned int"
.LASF148:
	.string	"EVENT_CDC_Device_LineEncodingChanged"
.LASF14:
	.string	"CDC_LINEENCODING_OneAndAHalfStopBits"
.LASF3:
	.string	"unsigned char"
.LASF96:
	.string	"PM_Adjust_AVDD_WL"
.LASF95:
	.string	"PM_Adjust_AVDD_WR"
.LASF77:
	.string	"_mVolt"
.LASF117:
	.string	"PM_Enable_AVDD_RRAM"
.LASF112:
	.string	"_mask"
.LASF162:
	.string	"CDC_Device_SendByte"
.LASF45:
	.string	"USB_ClassInfo_CDC_Device_t"
.LASF109:
	.string	"PM_ReadReg"
.LASF21:
	.string	"CDC_PARITY_Mark"
.LASF134:
	.string	"__vector_10"
.LASF140:
	.string	"ReceivedByte"
.LASF2:
	.string	"signed char"
.LASF114:
	.string	"PM_Enable_AVDD_WL"
.LASF15:
	.string	"CDC_LINEENCODING_TwoStopBits"
.LASF115:
	.string	"PM_Enable_AVDD_WR"
.LASF171:
	.string	"main"
.LASF17:
	.string	"CDC_LineEncodingParity_t"
.LASF54:
	.string	"__iCliRetVal"
.LASF56:
	.string	"__ToDo"
.LASF154:
	.string	"TxLEDPulse"
.LASF72:
	.string	"_size"
.LASF61:
	.string	"double"
.LASF119:
	.string	"PM_Enable_VDD"
.LASF39:
	.string	"ParityType"
.LASF168:
	.string	"rram-usbserial.c"
.LASF165:
	.string	"CDC_Device_ConfigureEndpoints"
.LASF101:
	.string	"cycles"
.LASF80:
	.string	"wdt_disable"
.LASF41:
	.string	"ControlLineStates"
.LASF153:
	.string	"__vector_23"
.LASF151:
	.string	"EVENT_CDC_Device_ControLineStateChanged"
.LASF38:
	.string	"CharFormat"
.LASF98:
	.string	"Data"
.LASF123:
	.string	"PM_Disable_VDD"
	.ident	"GCC: (AVR_8_bit_GNU_Toolchain_3.6.2_1778) 5.4.0"
.global __do_copy_data
.global __do_clear_bss
