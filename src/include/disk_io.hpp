#pragma once
#include <fstream>
#include <cstdint>
#include <memory>
#include <disk_info.hpp>

#define CACHE_MAX 512

class ErrorChannel;

class DiskIO
{
public:
    DiskIO(DiskInfo& diskInfo, ErrorChannel& channel);
    int Read(uint64_t lba, uint32_t sector_count, void* buf);
    int Write(uint64_t lba, uint32_t sector_count, void* buf);
    void PrintDiskInfo();
    void Dump();
    ~DiskIO();
private:
    std::fstream m_io;
    DiskInfo& m_diskInfo;
    std::string m_path;
    uint8_t cache[CACHE_MAX];
    ErrorChannel& m_err_channel;
private:
    void Initialize();
};