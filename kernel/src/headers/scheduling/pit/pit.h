#pragma once
#ifndef _PIT_H
#define _PIT_H

#include <stdint.h>

namespace PIT
{
    extern double TimeSinceBoot;
    const uint64_t BaseFrequency = 1193182;

    void Sleepd(double seconds);
    void Sleep(uint64_t milliseconds);

    void SetDivisor(uint16_t divisor);
    uint64_t GetFrequency();
    void SetFrequecy(uint64_t frequency);
    void Tick();
}

#endif // _PIT_H