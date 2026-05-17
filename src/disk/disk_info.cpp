#include <disk_info.hpp>
#include <iostream>
#include <error.hpp>

DiskInfo::DiskInfo(const char *path, ErrorChannel& channel) : 
m_devpath(path), 
m_devname(), 
m_err_channel(channel)
{
    ParsePath();
}

void DiskInfo::PrintInfo()
{
    if (m_err_channel.HasError()) return;
    std::cout << "Logical block size: " << logical_sector_size << "\n";
    std::cout << "Physical block size: " << physical_sector_size << "\n";
    std::cout << "Minimum IO size: " << min_io_size << "\n";
    std::cout << "Optimal IO size: " << best_io_size << "\n";
    std::cout << "Total sector count: " << total_sector_count << "\n";
}


const std::string &DiskInfo::GetDevicePath()
{
    return m_devpath;
}