#pragma once

struct BootInfo
{
    Framebuffer *framebuffer;
    PSF1_FONT *psf1_Font;
    void *mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
};

extern "C" void _start(BootInfo *bootInfo);