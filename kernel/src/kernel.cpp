// Need to fix/rework code to not have to include all files
#include "Terminal.cpp"
#include "Color.h"
#include "IO/IO.cpp"
#include "Interrupts/IDT.h"
#include "Interrupts/IDT.cpp"
#include "Input/Keyboard.h"
#include "Input/Keyboard.cpp"
//#include "Memory/MemoryMap.hpp"
#include "Memory/MemoryMap.cpp" // Dont want this one to just be the .cpp file, need to move to hpp

extern "C" void _start(){
	// Initialize different things
	IDT::InitializeIDT();
	Terminal::InitializeTerminal();
	Terminal::clearTerminal();
	Terminal::setCursorPosition(0);
	//Set the main keyboard handler of the IDT to the standard keyboard handler
	IDT::MainKeyboardHandler = Keyboard::standardKBHandler;

	for(byte i = 0; i < MemoryRegionCount; i++){
		MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000; //Memory address was as defined in DetectMemory.asm
		memMap += i;
		printMemoryMap(memMap, Terminal::cursorPos);
		Terminal::outputString("\n\n\r");
	}
	return;
}