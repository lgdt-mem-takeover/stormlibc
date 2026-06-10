default rel


;array to integer
global sasm_atou32
global sasm_atou64
global sasm_atoi32
global sasm_atoi64


;integer to array
global sasm_utoa64
global sasm_utoa32
global sasm_itoa64
global sasm_itoa32

%define ASCIIZ '0'
%define DIV10_MAGIC 0xCCCCCCCD

section .text


%ifdef WIN64
	%define param1_64 rcx
	%define param2_64 rdx
	%define param3_64 r8
	%define param4_64 r9
	%define param1_32 ecx
	%define param2_32 edx
	%define param3_32 r8d
	%define param4_32 r9d
%else
	%define param1_64 rdi
	%define param2_64 rsi
	%define param3_64 rdx
	%define param4_64 rcx
	%define param5_64 r8
	%define param6_64 r9
	%define param1_32 edi
	%define param2_32 esi
	%define param3_32 edx
	%define param4_32 ecx
	%define param5_32 r8d
	%define param6_32 r9d
%endif

;returns 64 bit unsigned integer
%define param1_string64 param1_64
%define param1_string32 param1_32
%define param2_string_len64 param2_64
%define param2_string_len32 param2_32
%define loop_counter32 r11d
%define loop_counter64 r11
%define temp_scratch32 r10d
%define temp_scratch64 r10
sasm_atou64:
	xor loop_counter64, loop_counter64
	xor rax, rax

.loop:
	cmp loop_counter32, param2_string_len32
	jae .exit_regular

	movzx temp_scratch32, byte [param1_string64 + loop_counter64]
	sub temp_scratch32, ASCIIZ
	lea rax, [rax + rax * 4]
	lea rax, [rax + rax]
	add rax, temp_scratch64


	inc loop_counter32
	jmp .loop


.exit_regular:
	ret

%undef param1_string64
%undef param1_string32
%undef param2_string_len64
%undef param2_string_len32
%undef loop_counter32
%undef loop_counter64
%undef temp_scratch32
%undef temp_scratch64

;returns 32 bit unsigned integer
%define param1_string64 param1_64
%define param1_string32 param1_32
%define param2_string_len64 param2_64
%define param2_string_len32 param2_32
%define loop_counter32 r11d
%define loop_counter64 r11
%define temp_scratch32 r10d
%define temp_scratch64 r10
sasm_atou32:
	xor loop_counter64, loop_counter64
	xor eax, eax

.loop:
	cmp loop_counter32, param2_string_len32
	jae .exit_regular

	movzx temp_scratch32, byte [param1_string64 + loop_counter64]
	sub temp_scratch32, ASCIIZ
	lea eax, [eax + eax * 4]
	lea eax, [eax + eax]
	add eax, temp_scratch32


	inc loop_counter32
	jmp .loop

.exit_regular:
	ret
%undef param1_string64
%undef param1_string32
%undef param2_string_len64
%undef param2_string_len32
%undef loop_counter32
%undef loop_counter64
%undef temp_scratch32
%undef temp_scratch64


;returns 32 bit signed integer
%define param1_string64 param1_64
%define param1_string32 param1_32
%define param2_string_len64 param2_64
%define param2_string_len32 param2_32
%define loop_counter32 r11d
%define loop_counter64 r11
%define temp_scratch32 r10d
%define temp_scratch64 r10
sasm_atoi32:
	xor loop_counter64, loop_counter64
	xor eax, eax

	cmp byte [param1_string64 + loop_counter64], '-' ;loop_counter32 is 0 here
	je .loop_signed_advance

.loop:
	cmp loop_counter32, param2_string_len32
	jae .exit_regular

	movzx temp_scratch32, byte [param1_string64 + loop_counter64]
	sub temp_scratch32, ASCIIZ
	lea eax, [eax + eax * 4]
	lea eax, [eax + eax]
	add eax, temp_scratch32

.loop_advance:
	inc loop_counter32
	jmp .loop


.loop_signed:
	cmp loop_counter32, param2_string_len32
	jae .exit_signed

	movzx temp_scratch32, byte [param1_string64 + loop_counter64]
	sub temp_scratch32, ASCIIZ
	lea eax, [eax + eax * 4]
	lea eax, [eax + eax]
	add eax, temp_scratch32


.loop_signed_advance:
	inc loop_counter32
	jmp .loop_signed


.exit_regular:
	ret

.exit_signed:
	neg eax
	ret

%undef param1_string64
%undef param1_string32
%undef param2_string_len64
%undef param2_string_len32
%undef loop_counter32
%undef loop_counter64
%undef temp_scratch32
%undef temp_scratch64

;returns 64 bit signed integer
%define param1_string64 param1_64
%define param1_string32 param1_32
%define param2_string_len64 param2_64
%define param2_string_len32 param2_32
%define loop_counter32 r11d
%define loop_counter64 r11
%define temp_scratch32 r10d
%define temp_scratch64 r10
sasm_atoi64:
	xor loop_counter64, loop_counter64
	xor rax, rax

	cmp byte [param1_string64 + loop_counter64], '-' ;loop_counter64 here is 0
	je .loop_signed_advance

.loop:
	cmp loop_counter32, param2_string_len32
	jae .exit_regular

	movzx temp_scratch64, byte [param1_string64 + loop_counter64]
	sub temp_scratch64, ASCIIZ
	lea rax, [rax + rax * 4]
	lea rax, [rax + rax]
	add rax, temp_scratch64

	inc loop_counter32
	jmp .loop


.loop_signed:
	cmp loop_counter32, param2_string_len32
	jae .exit_signed

	movzx temp_scratch64, byte [param1_string64 + loop_counter64]
	sub temp_scratch64, ASCIIZ
	lea rax, [rax + rax * 4]
	lea rax, [rax + rax]
	add rax, temp_scratch64

.loop_signed_advance:
	inc loop_counter32
	jmp .loop_signed

.exit_regular:
	ret

.exit_signed:
	neg rax
	ret

%undef param1_string64
%undef param1_string32
%undef param2_string_len64
%undef param2_string_len32
%undef loop_counter32
%undef loop_counter64
%undef temp_scratch32
%undef temp_scratch64





;returns integer length (eg: 1234 returns 4)
%define integer_len32 r11d
%define integer_len64 r11
%define loop_counter32 r9d
%define loop_counter64 r9
%define end_offset32 r10d
%define end_offset64 r10
%define buffer_out64 param1_64
%define buffer_out32 param1_32
%define value_in32 param2_32
%define value_in64 param2_64
sasm_utoa32:
	xor loop_counter32, loop_counter32
	jmp .integer_len


.loop:
	cmp loop_counter32, integer_len32
	jae .exit_regular

	dec end_offset32

	mov eax, value_in32
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35
	mov value_in32, r8d

	lea r8, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d
	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32
	jmp .loop

.integer_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in32, 10
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 10000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 10000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000000000
	cmovae integer_len32, eax
	mov end_offset32, integer_len32
	mov eax, value_in32
	jmp .loop

.exit_regular:
	mov eax, integer_len32
	ret

%undef integer_len32
%undef integer_len64
%undef loop_counter32
%undef loop_counter64
%undef end_offset32
%undef end_offset64
%undef quotient32
%undef quotient64
%undef remainder8
%undef remainder32
%undef remainder64
%undef temp_scratch_char8
%undef temp_scratch_char32
%undef temp_scratch_char64
%undef buffer_out64
%undef buffer_out32
%undef value_in32
%undef value_in64

;returns integer length (eg: 1234 returns 4)
%define integer_len32 r11d
%define integer_len64 r11
%define loop_counter32 r9d
%define loop_counter64 r9
%define end_offset32 r10d
%define end_offset64 r10
%define buffer_out64 param1_64
%define buffer_out32 param1_32
%define value_in32 param2_32
%define value_in64 param2_64
sasm_utoa64:
	xor loop_counter32, loop_counter32
	jmp .integer_len


.loop:
	cmp loop_counter32, integer_len32
	jae .exit_regular

	dec end_offset32

	mov rax, value_in64
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35
	mov value_in64, r8

	lea r8, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d
	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32
	jmp .loop

.integer_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in64, 10
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 10000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 10000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000000000
	cmovae integer_len32, eax
	mov end_offset32, integer_len32
	mov rax, value_in64
	jmp .loop

.exit_regular:
	mov eax, integer_len32
	ret

%undef integer_len32
%undef integer_len64
%undef loop_counter32
%undef loop_counter64
%undef end_offset32
%undef end_offset64
%undef quotient32
%undef quotient64
%undef remainder8
%undef remainder32
%undef remainder64
%undef temp_scratch_char8
%undef temp_scratch_char32
%undef temp_scratch_char64
%undef buffer_out64
%undef buffer_out32
%undef value_in32
%undef value_in64


;returns integer length (eg: 1234 returns 4)
%define integer_len32 r11d
%define integer_len64 r11
%define loop_counter32 r9d
%define loop_counter64 r9
%define end_offset32 r10d
%define end_offset64 r10
%define buffer_out64 param1_64
%define buffer_out32 param1_32
%define value_in32 param2_32
%define value_in64 param2_64
sasm_itoa32:
	xor loop_counter32, loop_counter32
	test value_in32, value_in32
	js .integer_signed_len
	jmp .integer_len


.loop:
	cmp loop_counter32, integer_len32
	jae .exit_regular

	dec end_offset32

	;start division by 10
	mov eax, value_in32
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35 ;finishes division by 10
	mov value_in32, r8d ; set up next value for value_in32 for next iteration

	;start multiply by 10
	lea r8d, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d ;finishes mod 10 remainder extraction
	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32
	jmp .loop


.loop_signed_post:
	dec end_offset64
	mov byte [buffer_out64 + end_offset64], '-'
	inc integer_len32 ;integer_len32 is moved into eax so we need to accomodate the length for the -
	jmp .exit_regular

.loop_signed:
	cmp loop_counter32, integer_len32
	jae .loop_signed_post

	dec end_offset64

	;start division by 10
	mov eax, value_in32
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35 ; finishes division by 10
	mov value_in32, r8d ; set up next value for value_in32 for next iteration

	;start multiply by 10
	lea r8d, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d

	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32

	jmp .loop_signed


.integer_signed_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in32, -10
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -100
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -1000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -10000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -100000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -1000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -10000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -100000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in32, -1000000000
	cmovle integer_len32, eax
	mov end_offset32, integer_len32
	inc end_offset32
	neg value_in32
	mov eax, value_in32
	jmp .loop_signed

.integer_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in32, 10
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 10000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 10000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 100000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in32, 1000000000
	cmovae integer_len32, eax
	mov end_offset32, integer_len32
	xor loop_counter32, loop_counter32
	mov eax, value_in32
	jmp .loop

.exit_regular:
	mov eax, integer_len32
	ret

%undef integer_len32
%undef integer_len64
%undef loop_counter32
%undef loop_counter64
%undef end_offset32
%undef end_offset64
%undef quotient32
%undef quotient64
%undef remainder8
%undef remainder32
%undef remainder64
%undef temp_scratch_char8
%undef temp_scratch_char32
%undef temp_scratch_char64
%undef buffer_out64
%undef buffer_out32
%undef value_in32
%undef value_in64



;returns integer length (eg: 1234 returns 4)
%define integer_len32 r11d
%define integer_len64 r11
%define loop_counter32 r9d
%define loop_counter64 r9
%define end_offset32 r10d
%define end_offset64 r10
%define buffer_out64 param1_64
%define buffer_out32 param1_32
%define value_in32 param2_32
%define value_in64 param2_64
sasm_itoa64:
	xor loop_counter32, loop_counter32
	test value_in64, value_in64
	js .integer_signed_len
	jmp .integer_len


.loop:
	cmp loop_counter32, integer_len32
	jae .exit_regular

	dec end_offset32

	;start division by 10
	mov rax, value_in64
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35 ;finishes division by 10
	mov value_in64, r8 ; set up next value for value_in32 for next iteration

	;start multiply by 10
	lea r8d, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d ;finishes mod 10 remainder extraction
	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32
	jmp .loop


.loop_signed_post:
	dec end_offset64
	mov byte [buffer_out64 + end_offset64], '-'
	inc integer_len32 ;integer_len32 is moved into eax so we need to accomodate the length for the -
	jmp .exit_regular

.loop_signed:
	cmp loop_counter32, integer_len32
	jae .loop_signed_post

	dec end_offset64

	;start division by 10
	mov rax, value_in64
	mov r8, DIV10_MAGIC
	imul r8, rax
	shr r8, 35 ; finishes division by 10
	mov value_in64, r8 ; set up next value for value_in32 for next iteration

	;start multiply by 10
	lea r8d, [r8 + r8 * 4]
	add r8, r8
	sub eax, r8d

	add eax, ASCIIZ

	mov byte [buffer_out64 + end_offset64], al

	inc loop_counter32

	jmp .loop_signed


.integer_signed_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in64, -10
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -100
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -1000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -10000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -100000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -1000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -10000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -100000000
	cmovle integer_len32, eax

	inc eax
	cmp value_in64, -1000000000
	cmovle integer_len32, eax
	mov end_offset32, integer_len32
	inc end_offset32
	neg value_in64
	mov rax, value_in64
	jmp .loop_signed

.integer_len:
	mov integer_len32, 1

	mov eax, 2
	cmp value_in64, 10
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 10000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 10000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 100000000
	cmovae integer_len32, eax

	inc eax
	cmp value_in64, 1000000000
	cmovae integer_len32, eax
	mov end_offset32, integer_len32
	xor loop_counter32, loop_counter32
	mov rax, value_in64
	jmp .loop

.exit_regular:
	mov eax, integer_len32
	ret

%undef integer_len32
%undef integer_len64
%undef loop_counter32
%undef loop_counter64
%undef end_offset32
%undef end_offset64
%undef quotient32
%undef quotient64
%undef remainder8
%undef remainder32
%undef remainder64
%undef temp_scratch_char8
%undef temp_scratch_char32
%undef temp_scratch_char64
%undef buffer_out64
%undef buffer_out32
%undef value_in32
%undef value_in64


section .note.GNU-stack noalloc noexec nowrite progbits
