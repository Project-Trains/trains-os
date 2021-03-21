#pragma once

struct BootInfo
{
    Framebuffer *framebuffer;
    PSF1_FONT *psf1_Font;
    EFI_MEMORY_DESCRIPTOR *mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
};

extern "C" void _start(BootInfo *bootInfo);