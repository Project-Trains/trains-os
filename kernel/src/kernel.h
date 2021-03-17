
typedef unsigned long long size_t;

typedef struct
{
    void *BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;
} Framebuffer;

typedef struct
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct
{
    PSF1_HEADER *psf1_Header;
    void *glyphBuffer;
} PSF1_FONT;

typedef struct
{
    unsigned int X;
    unsigned int Y;
} Point;

void putChar(Framebuffer *framebuffer, PSF1_FONT *psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void Print(Framebuffer *framebuffer, PSF1_FONT *psf1_font, unsigned int colour, char *str);
void _start(Framebuffer *framebuffer, PSF1_FONT *psf1_font);