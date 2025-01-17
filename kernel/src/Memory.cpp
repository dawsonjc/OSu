#include <memory.h>

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize)
{
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0)
        return memorySizeBytes; // Memory has already been calculated

    //Loop through each map entry and increment the sizebytes by the size of each entry
    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096; //Add the map size in bytes
    }

    return memorySizeBytes;
}

void memset(void* start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++) {
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}