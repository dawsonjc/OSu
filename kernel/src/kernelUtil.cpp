#include "kernelUtil.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL;
void PrepareMemory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize; // get the total map entries by dividing the size of the map by the descriptor size

    GlobalAllocator = PageFrameAllocator(); // Declare the global allocator to an instance of a PageFrameAllocator
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    // Get the kernel size 
    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 0x1000 + 1;
    
    // Lock the pages that correspond to kernel to prevent corrupting the kernel's code 
    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    //Set the page table
    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    for(uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t += 0x1000){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }  

    // Calculate the frame buffer size
    uint64_t fbBase = (uint64_t)bootInfo->frameBuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->frameBuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);
    for(uint64_t t = fbBase; t < fbBase + fbSize; t += 0x1000){
        pageTableManager.MapMemory((void*)t, (void*)t); //Map the frame buffer pages to virtual memory
    }

    asm("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &pageTableManager;
}

KernelInfo InitializeKernel(BootInfo* bootInfo){
    PrepareMemory(bootInfo);
    memset(bootInfo->frameBuffer->BaseAddress, 0, bootInfo->frameBuffer->BufferSize);
    return kernelInfo;
}