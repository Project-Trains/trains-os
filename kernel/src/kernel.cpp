#include <stdint.h>
#include "Renderer.h"
#include "cstr.h"
#include "kernel.h"

void _start(BootInfo *bootInfo)
{
    Renderer renderer = Renderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    renderer.Print(to_string((uint64_t)1234976));
    return;
}