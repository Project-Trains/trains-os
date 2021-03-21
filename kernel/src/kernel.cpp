#include <stdint.h>
#include "Renderer.h"
#include "cstr.h"
#include "kernel.h"
#include "efiMemory.h"
#include "memory.h"

void _start(BootInfo *bootInfo)
{
    Renderer renderer = Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    renderer.Print(to_string(GetMemorySize(bootInfo->framebuffer, bootInfo->psf1_Font) / 1024));
    renderer.Print(" KB");

    /*for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
        renderer.CursorPosition = {0, renderer.CursorPosition.Y + 16};
        renderer.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
        renderer.Color = 0xffffff00;
        renderer.Print(" ");
        renderer.Print(to_string(desc->numPages * 4096 / 1024));
        renderer.Print(" KB");
        renderer.Color = 0xffffffff;
    }*/
    return;
}