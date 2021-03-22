#include <stdint.h>
#include "Renderer.h"
#include "cstr.h"
#include "kernel.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"

void _start(BootInfo *bootInfo)
{
    Renderer renderer = Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    // renderer.Print(to_string(GetMemorySize(bootInfo->framebuffer, bootInfo->psf1_Font) / 1024));
    // renderer.Print(" KB");

    uint8_t buffer[20];
    Bitmap bitmap;
    bitmap.Buffer = &buffer[0];
    bitmap.Set(0, false);
    bitmap.Set(1, true);
    bitmap.Set(2, false);
    bitmap.Set(3, true);
    bitmap.Set(4, false);
    bitmap.Set(5, true);

    for (int i = 0; i < 20; i++)
    {
        renderer.CursorPosition = {16, renderer.CursorPosition.Y + 16};
        renderer.Print(bitmap[i] ? "true" : "false");
    }

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