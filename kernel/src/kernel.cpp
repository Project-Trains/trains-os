#include "kernel.h"

uint64_t _KernelStart;
uint64_t _KernelEnd;

void _start(BootInfo *bootInfo)
{
    Renderer renderer = Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    PageFrameAlloc allocator;
    allocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t) & _KernelEnd - (uint64_t) & _KernelStart;
    uint64_t kernelPages = (uint64_t) kernelSize / 4096 + 1;

    allocator.LockPages(&_KernelStart, kernelPages);

    renderer.CursorPosition = {0, renderer.CursorPosition.Y + 16};
    renderer.Print("Free RAM: ");
    renderer.Print(to_string(allocator.GetFreeRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = {0, renderer.CursorPosition.Y + 16};

    renderer.Print("Used RAM: ");
    renderer.Print(to_string(allocator.GetUsedRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = {0, renderer.CursorPosition.Y + 16};

    renderer.Print("Reserved RAM: ");
    renderer.Print(to_string(allocator.GetReservedRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = {0, renderer.CursorPosition.Y + 16};

    return;
}