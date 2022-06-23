#include <kernelUtil.h>

#include "Rust.h"


extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer.PrintLine("Kernel Initialized Successfully", 0xFF00FF00);

    int testValue = testFunction(true, true);

    GlobalRenderer.PrintLine("Test Vale init: ");

    while (true) {
        asm("hlt");
    }
}