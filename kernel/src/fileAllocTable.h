#pragma once

#include <stdint.h>
#include "string.h"

#define END_CLUSTER_32 0x0FFFFFF8
#define BAD_CLUSTER_32 0x0FFFFFF7
#define FREE_CLUSTER_32 0x00000000
#define END_CLUSTER_16 0xFFF8
#define BAD_CLUSTER_16 0xFFF7
#define FREE_CLUSTER_16 0x0000
#define END_CLUSTER_12 0xFF8
#define BAD_CLUSTER_12 0xFF7
#define FREE_CLUSTER_12 0x000

#define CLEAN_EXIT_BMASK_16 0x8000
#define HARD_ERR_BMASK_16 0x4000
#define CLEAN_EXIT_BMASK_32 0x08000000
#define HARD_ERR_BMASK_32 0x04000000

#define FILE_READ_ONLY 0x01
#define FILE_HIDDEN 0x02
#define FILE_SYSTEM 0x04
#define FILE_VOLUME_ID 0x08
#define FILE_DIRECTORY 0x10
#define FILE_ARCHIVE 0x20
#define FILE_LONG_NAME (FILE_READ_ONLY|FILE_HIDDEN|FILE_SYSTEM|FILE_VOLUME_ID)
#define FILE_LONG_NAME_MASK (FILE_READ_ONLY|FILE_HIDDEN|FILE_SYSTEM|FILE_VOLUME_ID|FILE_DIRECTORY|FILE_ARCHIVE)
#define FILE_LAST_LONG_ENTRY 0x40
#define ENTRY_FREE 0xE5
#define ENTRY_END 0x00
#define ENTRY_JAPAN 0x05
#define LAST_LONG_ENTRY 0x40

#define LOWERCASE_ISSUE 0x01
#define BAD_CHARACTER 0x02
#define BAD_TERMINATION 0x04
#define NOT_CONVERTED_YET 0x08
#define TOO_MANY_DOTS 0x10

#define GET_CLUSTER_FROM_ENTRY(x) (x.low_bits | (x.high_bits << (fat_type / 2)))
#define GET_ENTRY_LOW_BITS(x) (x & ((fat_type /2) -1))
#define GET_ENTRY_HIGH_BITS(x) (x >> (fat_type / 2))
#define CONCAT_ENTRY_HL_BITS(high, low) ((high << (fat_type / 2)) | low)

typedef struct fatExtBs32
{
    uint32_t tableSize32;
    uint16_t extendedFlags;
    uint16_t fatVersion;
    uint32_t rootCluster;
    uint16_t fatInfo;
    uint16_t backupBsSector;
    uint8_t reserved0[12];
    uint8_t driveNumber;
    uint8_t reserved1;
    uint8_t bootSignature;
    uint32_t volumeId;
    uint8_t volumeLabel[11];
    uint8_t fatTypeLabel[8];
} __attribute__((packed)) fatExtBs32T;
typedef struct fatExtBs16
{
    uint8_t biosDriveNum;
    uint8_t reserved1;
    uint8_t bootSignature;
    uint32_t volumeId;
    uint8_t volumeLabel[11];
    uint8_t fatTypeLabel[8];
} __attribute__((packed)) fatExtBs16T;
typedef struct fatBs
{
    uint8_t bootjmp[3];
    uint8_t oemName[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectorCount;
    uint8_t tableCount;
    uint16_t rootEntryCount;
    uint16_t totalSectors16;
    uint8_t mediaType;
    uint16_t tableSize16;
    uint16_t sectorsPerTrack;
    uint16_t headSideCount;
    uint32_t hiddenSectorCount;
    uint32_t totalSectors32;
    uint8_t extendedSection[54];
} __attribute__((packed)) fatBsT;
typedef struct directoryEntry
{
    uint8_t fileName[11];
    uint8_t attributes;
    uint8_t reserved0;
    uint8_t creationTimeTenths;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t lastAccessed;
    uint16_t highBits;
    uint16_t lastModificationTime;
    uint16_t lastModificationDate;
    uint16_t lowBits;
    uint32_t fileSize;
} __attribute__((packed)) directoryEntryT;
typedef struct fsInfo
{
    uint32_t leadSignature;
    uint8_t reserved1[480];
    uint32_t structureSignature;
    uint32_t freeSpace;
    uint32_t lastWritten;
    uint8_t reserved2[12];
    uint32_t trailSignature;
} __attribute__((packed)) fsInfoT;
typedef struct longEntry
{
    uint8_t order;
    uint8_t firstFive[10];
    uint8_t attributes;
    uint8_t type;
    uint8_t checksum;
    uint8_t nextSix[12];
    uint16_t zero;
    uint8_t lastTwo[4];
} __attribute__((packed)) longEntryT;
extern uint32_t fatType;
extern uint32_t firstFatSector;
extern uint32_t firstDataSector;
extern uint32_t totalClusters;
extern fatBsT bootsect;

class FAT
{
    int Init();
    int Read(uint32_t clusterNum);
    int Write(uint32_t clusterNum, uint32_t clusterVal);
};
