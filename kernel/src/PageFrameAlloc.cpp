#include "PageFrameAlloc.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialized = false;

void PageFrameAlloc::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescSize)
{
    if (Initialized)
        return;

    Initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;
    void *largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *) ((uint64_t) mMap + (i * mMapDescSize));
        if (desc->type == 7) {
            if (desc->numPages * 4096 > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memorySize;
    uint64_t bitmapSize = memorySize / 4096 / 8 + 1;

    InitBitmap(bitmapSize, largestFreeMemSeg);

    LockPages(&PageBitmap, PageBitmap.Size / 4096 + 1);

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *) ((uint64_t) mMap + (i * mMapDescSize));
        if (desc->type != 7)
            ReservePages(desc->physAddr, desc->numPages);
    }
}

void PageFrameAlloc::InitBitmap(size_t bitmapSize, void *bufferAddress)
{
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t *) bufferAddress;
    for (int i = 0; i < bitmapSize; i++)
        *(uint8_t * )(PageBitmap.Buffer + i) = 0;
}

void *PageFrameAlloc::RequestPage()
{
    for (uint64_t index = 0; index < PageBitmap.Size * 8; index++) {
        if (PageBitmap[index]) continue;
        LockPage((void *) (index * 4096));
        return (void *) (index * 4096);
    }

    return NULL;
}

void PageFrameAlloc::FreePage(void *address)
{
    uint64_t index = (uint64_t) address / 4096;
    if (!PageBitmap[index]) return;
    PageBitmap.Set(index, false);
    freeMemory += 4096;
    usedMemory -= 4096;
}

void PageFrameAlloc::FreePages(void *address, uint64_t pageCount)
{
    for (int t = 0; t < pageCount; t++)
        FreePage((void *) ((uint64_t) address + (t * 4096)));
}

void PageFrameAlloc::LockPage(void *address)
{
    uint64_t index = (uint64_t) address / 4096;
    if (PageBitmap[index]) return;
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    usedMemory += 4096;
}

void PageFrameAlloc::LockPages(void *address, uint64_t pageCount)
{
    for (int t = 0; t < pageCount; t++)
        LockPage((void *) ((uint64_t) address + (t * 4096)));
}

void PageFrameAlloc::UnreservePage(void *address)
{
    uint64_t index = (uint64_t) address / 4096;
    if (!PageBitmap[index]) return;
    PageBitmap.Set(index, false);
    freeMemory += 4096;
    reservedMemory -= 4096;
}

void PageFrameAlloc::UnreservePages(void *address, uint64_t pageCount)
{
    for (int t = 0; t < pageCount; t++)
        UnreservePage((void *) ((uint64_t) address + (t * 4096)));
}

void PageFrameAlloc::ReservePage(void *address)
{
    uint64_t index = (uint64_t) address / 4096;
    if (PageBitmap[index]) return;
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    reservedMemory += 4096;
}

void PageFrameAlloc::ReservePages(void *address, uint64_t pageCount)
{
    for (int t = 0; t < pageCount; t++)
        ReservePage((void *) ((uint64_t) address + (t * 4096)));
}

uint64_t PageFrameAlloc::GetFreeRAM()
{
    return freeMemory;
}

uint64_t PageFrameAlloc::GetUsedRAM()
{
    return usedMemory;
}

uint64_t PageFrameAlloc::GetReservedRAM()
{
    return reservedMemory;
}