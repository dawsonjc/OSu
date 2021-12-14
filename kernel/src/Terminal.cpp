#pragma once 

#include <Terminal.hpp>
#include <Typedefs.h>
#include <Color.h>
#include "IO/IO.hpp" 
#define VGA_MEMORY (uint8*)0xb8000 
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint8 cursorPos;

Terminal::Terminal(){}

void Terminal::InitializeTerminal(){
	ClearTerminal(BG_BLACK | FG_WHITE);
	SetCursorPosition(0);
}

void Terminal::ClearTerminal(uint64 color = BG_BLACK | FG_WHITE){
	uint64 val = 0;
	val += color << 8;
	val += color << 24;
	val += color << 40;
	val += color << 56;
	for(uint64* i = (uint64*)VGA_MEMORY; i < (uint64*)(VGA_MEMORY + 4000); i++){
		*i = val;
	}
}

void Terminal::SetCursorPosition(uint16 position){
	if(position >= 2000) // Check if the wanted position is out of bounds
		position = 1999; 

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8)((position >> 8) & 0xFF));

	cursorPos = position;
}

void Terminal::OutputString(const char* str, uint8 color = BG_BLACK | FG_WHITE){
	uint8* charPtr = (uint8*)str;
	uint16 index = cursorPos;

	while(*charPtr != 0){

		switch(*charPtr){
			case 0x0a: //New Line
				index += VGA_WIDTH;
				break;
			case 0x0d: //Return Carriage
				index -= index % VGA_WIDTH;
				break;
			default:
				*(VGA_MEMORY + index * 2) = *charPtr;
				*(VGA_MEMORY + index * 2 + 1) = color;
				index++;
		}
		charPtr++;
	}

	SetCursorPosition(index);
}

uint8 Terminal::CursorPositionCoords(uint8 x, uint8 y){
	// Might need ??
	// if(y >= VGA_HEIGHT)
	// 	y = VGA_HEIGHT - 1; //Set the Cursor y to the maximum it could be
	// if(x >= VGA_WIDTH)
	// 	x = VGA_WIDTH - 1; //Set the Cursor x to the maximum it could be

	return (y * VGA_WIDTH) + x;
}

char hexToStringOutput[128];
template<typename T>
const char* Terminal::HexToString(T value){
	T* valPtr = &value;
	uint8* ptr;
	uint8 temp;
	uint8 size = (sizeof(T)) * 2 - 1;

	for(uint8 i = 0; i < size; i++){
		ptr = ((uint8*)valPtr + i);
		temp = ((*ptr & 0xF0) >> 4);
		hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
		temp = (*ptr & 0x0F);
		hexToStringOutput[size - (i * 2)] = temp + (temp > 9 ? 55 : 48);
	}
	hexToStringOutput[size + 1] = 0;
	return hexToStringOutput;
}