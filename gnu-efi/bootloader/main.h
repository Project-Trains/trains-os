#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned long long size_t;

typedef struct
{
    void *BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;
} Framebuffer;

EFI_FILE *LoadFile(EFI_FILE *Directory, CHAR16 *Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);
int memcmp(const void *aptr, const void *bptr, size_t n);
BOOLEAN KernelFormatCheck(Elf64_Ehdr header);
Framebuffer *InitGOP();

#endif