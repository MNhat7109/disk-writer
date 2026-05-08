#pragma once
#include <cstdint>
#include <fstream>

struct DiskInfo
{
    DiskInfo(const char* path);
    void GetInfo();
    const std::string& GetDevicePath();
    const bool& GetError();

    void PrintInfo();
    
    friend class LinuxDiskHelperUtils;
    
    uint32_t logical_sector_size;
    uint32_t physical_sector_size;
    uint32_t min_io_size;
    uint32_t best_io_size;
    uint64_t total_sector_count;
    
    // 
private:
    void ParsePath();
    std::string m_devname, m_devpath;
    bool m_err;
};