get_input:						; start of the call
	pusha						; push all registers to stack for retrival later
	
	mov bp, 0x7b00				; Set the base pointer
	mov dx, bp					; Set dx to the base pointer
	mov sp, bp					; by default set the stack pointer to the base pointer since the stack is empyt
	mov cx, 0 					; Use cx as counter, mostly just for string formatting

loop_input:
	mov ah, 0x00
	cmp bl, 0x0d				; If the Scan code turns out to be 0x0d (return carriage) then jump to the end
	je print_input_loop
	int 0x16					; Read keyboard input

	mov bx, ax					; mov ax to bx
	and bx, 0x00ff				; get the scan codes character

	cmp bl, 0x08
	je remove_previous_character

	push bx						; push bx onto the stack

	mov ah, 0x0e				; Enter TTY mode
	mov al, bl					; print the value stored in bl to the BIOS
	int 0x10					; Call BIOS interrupt


	jmp loop_input
remove_previous_character:
	mov ah, 0x03				; get the curesor position on the console
	mov bh, 0 					; Set the page to 0
	int 0x10					; DH -> Row, DL -> Column


	;call print_new_line
	;call print_hex
	cmp dl, 0
	je loop_input


	cmp bp, sp
	je loop_input

	pop bx
	sub dl, 1

	mov ah, 0x02
	mov bh, 1
	;call print_new_line
	;call print_hex
	int 0x10

	mov ah, 0x0a
	mov al, 0
	mov bh, 0
	mov cx, 1
	int 0x10

	jmp loop_input

print_input_loop:
	cmp dx, sp
	je end_input_loop
	cmp cx, 0 					; Check to see if this is the first iteration of the print so it wont remove the user's inputted line
	je format_next_line				
	
	mov bx, dx					; get bx ready to print
	call print
	sub dx, 2 					; Move down the stack 2 bytes since the value for the character is every 2 bytes
	jmp print_input_loop

format_next_line:
	call print_new_line
	inc cx
	jmp print_input_loop

end_input_loop:					; end of the function
	cmp bx, [bp]				; Clear the stack
	pop bx						
	jne end_input_loop

	popa						; restore the previous stack
	ret							; return