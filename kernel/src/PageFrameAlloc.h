#pragma once
#include "efiMemory.h"
#include <stdint.h>
#include "Bitmap.h"
#include "memory.h"

class PageFrameAlloc
{
public:
    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap PageBitmap;

private:
    void InitBitmap(size_t bitmapSize, void *bufferAddress);
}