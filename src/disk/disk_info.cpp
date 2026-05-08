#include <disk_info.hpp>
#include <iostream>

DiskInfo::DiskInfo(const char *path) : m_devpath(path), m_devname(), m_err(false)
{
    ParsePath();
}

const bool& DiskInfo::GetError()
{
    return m_err;
}

void DiskInfo::PrintInfo()
{
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