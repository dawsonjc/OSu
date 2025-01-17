#pragma once
#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

/*** Common Gates ***/
#define IDT_TA_InterruptGate    0b10001110
#define IDT_TA_CallGate         0b10001100
#define IDT_TA_TrapGate         0b10001111

struct IDTDescEntry {
    uint16_t  offset0;
    uint16_t  selector;       // Segment selector
    uint8_t   ist;            // Interrupt stack table offset
    uint8_t   type_attr;
    uint16_t  offset1;
    uint32_t  offset2;
    uint32_t  ignore;
    void      SetOffset(uint64_t offset);
    uint64_t  GetOffset();
};

struct IDTR {
    uint16_t  Limit;
    uint64_t  Offset;
} __attribute__((packed));

#endif // _IDT_H