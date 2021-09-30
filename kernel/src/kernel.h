#pragma once

#include <stdint.h>
#include "Renderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "PageFrameAlloc.h"

struct BootInfo
{
    Framebuffer *framebuffer;
    PSF1_FONT *psf1_Font;
    EFI_MEMORY_DESCRIPTOR *mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
};
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo *bootInfo);