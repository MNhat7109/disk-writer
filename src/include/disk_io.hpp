#pragma once
#include <fstream>
#include <cstdint>
#include <disk_info.hpp>

#define CACHE_MAX 512

class DiskIO
{
public:
    DiskIO(const char* path);
    int Read(uint64_t lba, uint32_t sector_count, void* buf);
    int Write(uint64_t lba, uint32_t sector_count, void* buf);
    void Dump();
    ~DiskIO();
private:
    std::fstream f;
    DiskInfo diskInfo;
    uint8_t cache[CACHE_MAX];
};