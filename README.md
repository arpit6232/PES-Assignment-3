# PES-Assignment-1
Author: Arpit Savarkar

## Repository Comments 
_Contains_
Code for Assignment 3 for Principals of Embedded Systems Software, ECEN-5813, Fall 2020

### Repository for PES-Assignment 1 

Source Code for this assignment can be found under source/

- <b>Blinkenlights.c - The main script which demonstrates the start-up pattern and interaction between the slider and the LEDs on FRDM KL25Z </b>
- <b>led.h - Header file of led.c defining the led functions </b>
- <b>led.c - File containing LED Clock Gating Initialization and function which toggles LED Color </b>
- <b>delay.h - Header file of delay.c defining helper functions for busy waiting </b>
- <b>delay.c - File containing Busy waiting functionalities particularly, simple delay and conditional delay </b>


## Project Comments
This projects implements the following routine : <br />
- At program startup, Blinkenlights will “test” the LED by blinking in the following pattern: <br />
    - RED for 500 msec, OFF for 100 msec, <br />
    - GREEN for 500 msec, OFF for 100 msec, <br />
    - BLUE for 500 msec, OFF for 100 msec <br />
    - WHITE (that is, RED, GREEN, and BLUE all on) for 100 msec, OFF for 100 msec <br />
    - WHITE for 100 msec, OFF for 100 MSEC <br />

- Blinkenlights will then enter an infinite loop where the LED will be flashed using the following pattern: <br />
    - ON for 500 msec, OFF for 500 msec, <br />
    - ON for 1000 msec, OFF for 500 msec, <br />
    - ON for 2000 msec, OFF for 500 msec, <br />
    - ON for 3000 msec, OFF for 500 msec <br />
    - Go back to the top (e.g., ON for 500 msec...) <br />

- During the infinite loop, the color when the LED is ON will initially be white. If the user touches the capacitive touch slider, the color will change as follows:  <br />
    - User touches Color <br />
    - Left side of slider Red <br />
    - Center of slider Green <br />
    - Right side of slider Blue <br />
(There is no way to get back to white after touching the slider.) <br />
The Blinkenlights code polls the touch slider once every 100 msec. If the LED is on when a
touch is detected, the light color should change immediately.

## Disassembly (Extra Credit)
* What is the address of your main() function? <br />
From the Disassembly of Blinkinlights.o the following is observed .text segment <br />
Sections: <br />
Idx Name          Size      VMA       LMA       File off  Algn  <br />
 26 .text         00000000  00000000  00000000  0000016c  2**1  <br />
                  CONTENTS, ALLOC, LOAD, READONLY, CODE         <br />
----------------------------------------------------------------------------- <br />
 35 .text.main    00000130  00000000  00000000  </b>0000024c</b>  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE

The Starting Address of main resides in .text.main which here </b>0000024c</b>

* What is the size in bytes of your delay() function, as shown by objdump? <br />
For my implementation I have used to types of Delay functions both of whose details are mentioned here <br />
From the Disassembly of delay.o the following is observed .text segment <br />
Sections: <br />
Idx Name                    Size      VMA       LMA       File off  Algn  <br />
 27 .text.Delay             0000002e  00000000  00000000  00000160  2**1  <br />
                            CONTENTS, ALLOC, LOAD, READONLY, CODE    <br />
                            <br />
 28 .text.conditional_Delay 00000064  00000000  00000000  00000190  2**2  <br />
                            CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE  <br />

The Size of "Delay()" as described by the objdump here showcases to be 0x0000002e which is stored along with a 2**1 allignment offset <br />
The Size of "conditional_Delay()" as described by the objdump here showcases to be 0x00000064 which is stored along with a 2**2 allignment offset <br />


* Show the full disassembly of your delay() function, adding comments to each line to explain the functionality. <br />
The following disassembly showcases two sections which represent the disassembly of the two types of implementations of Delay  <br />

Registers r4 through r11 are preserved across function calls. Since the function uses these registers, then the prolog will save these
registers on the stack with the push Instruction

Disassembly of section .text.Delay:

00000000 <Delay>: <br />
__ <br />
#### Registers r4 through r11 are preserved across function calls. Since the function uses these registers, then the prolog will save these registers on the stack with the push Instruction <br />
#### As the function makes a subroutine call, return address LR is also store <br />
#### Push Link Register and r7 onto stack
   0:	b580      	push	{r7, lr} <br />
   <br />

#### Grow the stack by subtracting literal 8 from the stack pointer (grows downwards)
   2:	b082      	sub	sp, #8 <br />
   <br />

#### Adds the contents of sp and #0 , writing the result to r7
   4:	af00      	add	r7, sp, #0 <br />
    <br />

#### Store R0 to the memory word (4 bytes) starting at location R7 + #4
   6:	6078      	str	r0, [r7, #4] <br />
   <br />

#### Load register r2 with the contents of the memory word (4 bytes) starting r7 + 4
   8:	687a      	ldr	r2, [r7, #4] <br />
   <br />

#### Move the contents of r2 to r3, S is the condition flags are updated on the result of the operation.
   a:	0013      	movs	r3, r2 <br /> 
   <br />

#### Logical Shifted condition shifted by #5 back into r3, S implies condition @ r3:=r3<<5
   c:	015b      	lsls	r3, r3, #5 <br /> 
   <br />

#### Subtract r2 from r3 and store it back in r3
   e:	1a9b      	subs	r3, r3, r2 <br /> 
   <br />

#### Logical Shifted condition shifted by #2 back into r3 @ r3:=r3<<2
  10:	009b      	lsls	r3, r3, #2 <br />
   <br />

#### Adds the content of r3 and r2, writing the result to r3
  12:	189b      	adds	r3, r3, r2 <br />
   <br />

#### Logical Shifted condition shifted by #3 back into r3 @ r3:=r3<<3
  14:	00db      	lsls	r3, r3, #3 <br />
    <br />

#### Store r3 to the memory word (4 bytes) starting at location R7 + #4
  16:	607b      	str	r3, [r7, #4] <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  18:	46c0      	nop			; (mov r8, r8) <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 4
  1a:	687b      	ldr	r3, [r7, #4] <br />
    <br />

#### Subtract #1 from r3 and store it into r2
  1c:	1e5a      	subs	r2, r3, #1 <br />
    <br />

#### Store R2 to the memory word (4 bytes) starting at location R7 + #4
  1e:	607a      	str	r2, [r7, #4] <br />
    <br />

#### Compares r3 with the immediate zero and sets the processor's condition code flags according to the result,
#### that is if r3 and zero are equal, Z Flag will be set to one, otherwise it will be cleared to zero
  20:	2b00      	cmp	r3, #0 <br />
    <br />

#### branches, or "jumps", to the address specified if, and only if the zero flag is clear. If the zero flag is set when the CPU 
#### encounters a BNE instruction, the CPU will continue at the instruction following the BNE rather than taking the jump. 
  22:	d1fa      	bne.n	1a <Delay+0x1a> <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  24:	46c0      	nop			; (mov r8, r8) <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  26:	46c0      	nop			; (mov r8, r8) <br />
   <br />

#### Move the contents of r7 to Stack Pointer
  28:	46bd      	mov	sp, r7 <br />
   <br />

#### Add #8 to sp , Decay the Stack 
  2a:	b002      	add	sp, #8 <br />
   <br />

#### Load Registers r7 and pc off the Stack
  2c:	bd80      	pop	{r7, pc}<br />
    <br />
    <br />
    <br />


Disassembly of section .text.conditional_Delay: <br />

00000000 <conditional_Delay>: <br />
#### Registers r4 through r11 are preserved across function calls. Since the function uses these registers, then the prolog will save these registers on the stack with the push Instruction <br />
#### As the function makes a subroutine call, return address LR is also store <br />
#### Save r4 and lr on the stack
   0:	b580      	push	{r7, lr} <br />
   <br />

#### Grow the stack by subtracting literal 8 from the stack pointer (grows downwards)
   2:	b084      	sub	sp, #16 <br />
   <br />

#### Adds the contents of sp and #0 , writing the result to r7
   4:	af00      	add	r7, sp, #0 <br />
    <br />

#### Store R0 to the memory word (4 bytes) starting at location R7 + #12
   6:	60f8      	str	r0, [r7, #12] <br />
    <br />

#### Store R1 to the memory word (4 bytes) starting at location R7 + #8
   8:	60b9      	str	r1, [r7, #8] <br />
    <br />

#### Store R2 to the memory word (4 bytes) starting at location R7 + #4
   a:	607a      	str	r2, [r7, #4] <br />
    <br />

#### Store R3 to the memory word (4 bytes) starting at location R7 + #0
   c:	603b      	str	r3, [r7, #0] <br />
    <br />

#### faults if label out of range for 16-bit instruction
   e:	e01c      	b.n	4a <conditional_Delay+0x4a> <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 12
  10:	68fb      	ldr	r3, [r7, #12] <br />
    <br />

#### Load register r2 with the contents of the memory word (4 bytes) starting r7 + 8
  12:	68ba      	ldr	r2, [r7, #8] <br />
   <br />

#### Move the contents of r2 to r1, S is the condition flags are updated on the result of the operation.
  14:	0011      	movs	r1, r2 <br />
   <br />

#### Move the contents of r3 to r0, S is the condition flags are updated on the result of the operation.
  16:	0018      	movs	r0, r3 <br />
   <br />

#### The BL instruction causes a branch to label, and copies the address of the next instruction into LR (R14, the link register).
#### If Condition of Modulo is satisfied
  18:	f7ff fffe 	bl	0 <__aeabi_uidivmod> <br />
			18: R_ARM_THM_CALL	__aeabi_uidivmod 

   <br />

#### Subtract #1 from r3 and store it into r2
  1c:	1e0b      	subs	r3, r1, #0 <br />
    <br />

#### branches, or "jumps", to the address specified if, and only if the zero flag is clear. If the zero flag is set when the CPU 
#### encounters a BNE instruction, the CPU will continue at the instruction following the BNE rather than taking the jump. 
  1e:	d114      	bne.n	4a <conditional_Delay+0x4a> <br />
   <br />

#### The BL instruction causes a branch to label, and copies the address of the next instruction into LR (R14, the link register).
#### If Condition of Modulo is satisfied, it stores the link register for the return CAP_Scan()
  20:	f7ff fffe 	bl	0 <CAP_Scan> <br />
			20: R_ARM_THM_CALL	CAP_Scan <br />
   <br />

#### Move the contents of r0 to r3, S is the condition flags are updated on the result of the operation.
  24:	0003      	movs	r3, r0 <br /> 
   <br />

#### Move the contents of r2 to r3, S is the condition flags are updated on the result of the operation.
  26:	001a      	movs	r2, r3 <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 4
  28:	687b      	ldr	r3, [r7, #4] <br />
    <br />

#### Store R2 to the memory word (4 bytes) starting at location R3 + #0
  2a:	601a      	str	r2, [r3, #0] <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 4
  2c:	687b      	ldr	r3, [r7, #4] <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r3 + 0
  2e:	681b      	ldr	r3, [r3, #0] <br />
    <br />

#### Compares r3 and 25, that is r3-25 and sets the flag accordingly.
  30:	2b19      	cmp	r3, #25 <br />
    <br />

#### Branch if less than equal, condition is satisfied
  32:	dd0a      	ble.n	4a <conditional_Delay+0x4a> <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 4
  34:	687b      	ldr	r3, [r7, #4] <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r3 + 0
  36:	681b      	ldr	r3, [r3, #0] <br />
    <br />

#### Load register r2 with the contents of the memory word (4 bytes) starting pc + 36
  38:	4a09      	ldr	r2, [pc, #36]	; (60 <conditional_Delay+0x60>) <br />
    <br />

#### Compares r3 and r2, that is r3-r2 and sets the flag accordingly.
  3a:	4293      	cmp	r3, r2 <br />
    <br />

#### Branch if greater than equal, condition is satisfied
  3c:	dc05      	bgt.n	4a <conditional_Delay+0x4a> <br />
    <br />

#### Load register r2 with the contents of the memory word (4 bytes) starting r7 + 0
  3e:	683a      	ldr	r2, [r7, #0] <br />
    <br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 4
  40:	687b      	ldr	r3, [r7, #4] <br />
   <br />

#### Move the contents of r2 to r1, S is the condition flags are updated on the result of the operation.
  42:	0011      	movs	r1, r2 <br />
   <br />

#### Move the contents of r0 to r3, S is the condition flags are updated on the result of the operation.
  44:	0018      	movs	r0, r3 <br />
    <br />

#### The BL instruction causes a branch to label, and copies the address of the next instruction into LR (R14, the link register).
#### If Condition of Modulo is satisfied, it stores the link register for the return helper_COLOR()
  46:	f7ff fffe 	bl	0 <helper_COLOR> <br /> 
			46: R_ARM_THM_CALL	helper_COLOR
    
<br />

#### Load register r3 with the contents of the memory word (4 bytes) starting r7 + 12
  4a:	68fb      	ldr	r3, [r7, #12] <br />
   <br />

#### Subtract 1 from r3 and store it in r2
  4c:	1e5a      	subs	r2, r3, #1 <br />
    <br />

#### Store R2 to the memory word (4 bytes) starting at location R7 + 12
  4e:	60fa      	str	r2, [r7, #12]  <br />
    <br />

#### Compares r3 with the immediate zero and sets the processor's condition code flags according to the result,
#### that is if r3 and zero are equal, Z Flag will be set to one, otherwise it will be cleared to zero
  50:	2b00      	cmp	r3, #0 <br />
    <br />

#### branches, or "jumps", to the address specified if, and only if the zero flag is clear. If the zero flag is set when the CPU 
#### encounters a BNE instruction, the CPU will continue at the instruction following the BNE rather than taking the jump. 
#### Satisfies the while condition for ELSE
  52:	d1dd      	bne.n	10 <conditional_Delay+0x10> <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  54:	46c0      	nop			; (mov r8, r8) <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  56:	46c0      	nop			; (mov r8, r8) <br />
   <br />

#### Move the contents of r7 to Stack Pointer
  58:	46bd      	mov	sp, r7 <br />  
   <br />

#### Add #16 to sp , Decay the Stack 
  5a:	b004      	add	sp, #16<br />
   <br />

#### Load Registers r7 and pc off the Stack
  5c:	bd80      	pop	{r7, pc} <br />
    <br />

#### No Operation Basically Move contents of r8 back to r8, Busy waiting scheme
  5e:	46c0      	nop			; (mov r8, r8) <br />
    <br />

#### .word is like unsigned int in C
  60:	0000ea5f 	.word	0x0000ea5f <br />


## Execution 
 - To run the Program (Linux) :
1) make
2) ./main
