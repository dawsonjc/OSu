#include <kernelUtil.h>

int testFunction(bool withValue, bool hasValue);

extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer.PrintLine("Kernel Initialized Successfully", 0xFF00FF00);

    int testValue = testFunction(true, true);

    GlobalRenderer.PrintLine("Test Vale init: ", testValue);

    while (true) {
        asm("hlt");
    }
}