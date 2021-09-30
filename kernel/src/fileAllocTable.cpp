#include "fileAllocTable.h"

uint32_t fatType;
uint32_t firstFatSector;
uint32_t firstDataSector;
uint32_t totalClusters;

int FAT::Init()
{
    return 0;
}

int FAT::Read(uint32_t clusterNum)
{
    return 0;
}

int FAT::Write(uint32_t clusterNum, uint32_t clusterVal)
{
    return 0;
}