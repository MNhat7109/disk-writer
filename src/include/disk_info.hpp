#pragma once
#include <cstdint>
#include <fstream>

struct DiskInfo
{
    static DiskInfo AsPath(const char* path);
    static DiskInfo AsDevName(const char* devname);
    void GetInfo();
    const bool& GetError();
    
    friend class LinuxDiskHelperUtils;
    
    uint32_t logical_sector_size;
    uint32_t physical_sector_size;
    uint32_t min_io_size;
    uint32_t best_io_size;
    uint64_t total_sector_count;
    // 
private:
    explicit DiskInfo(const char* string);
    const char* m_devname;
    bool m_err;
};