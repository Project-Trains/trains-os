#include <stdint.h>
#include "Renderer.h"
#include "cstr.h"
#include "kernel.h"

void _start(Framebuffer *framebuffer, PSF1_FONT *psf1_font)
{
    Renderer renderer = Renderer(framebuffer, psf1_font);
    renderer.Print(to_string((uint64_t)1234976));    
    return;
}