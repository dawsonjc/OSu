#include <kernelUtil.h>

#include "rusty/target/x86_64-unknown-uefi/release/Rust.h"


extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer.PrintLine("Kernel Initialized Successfully", 0xFF00FF00);

    int value = testFunction(true, true);

    GlobalRenderer.PrintLine("Test Vale init");

    while (true) {
        asm("hlt");
    }
}