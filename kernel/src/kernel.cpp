#include "kernel.h"

void putChar(Framebuffer *framebuffer, PSF1_FONT *psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)framebuffer->BaseAddress;
    char *fontPtr = (char *)psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
            }
        }
        fontPtr++;
    }
}

Point CursorPosition;
void Print(Framebuffer *framebuffer, PSF1_FONT *psf1_font, unsigned int colour, const char *str)
{

    char *chr = (char *)str;
    while (*chr != 0)
    {
        putChar(framebuffer, psf1_font, colour, *chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X += 8;
        if (CursorPosition.X + 8 > framebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
}

void _start(Framebuffer *framebuffer, PSF1_FONT *psf1_font)
{
    CursorPosition.X = 50;
    CursorPosition.Y = 120;
    Print(framebuffer, psf1_font, 0xffffffff, "Hello there!");
    return;
}