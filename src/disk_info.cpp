#include <disk_info.hpp>
#include <iostream>

#define INVALID_VALUE (uint64_t)-1
std::ifstream reader;

class LinuxDiskHelperUtils
{
public:
    uint64_t read_sysfs(DiskInfo& info, std::string path);
};


uint64_t LinuxDiskHelperUtils::read_sysfs(DiskInfo& info, std::string path)
{
    std::cout << "Reading info from disk...\n";
    std::cout << "Path: " << path << "\n";
    uint64_t value = INVALID_VALUE;
    reader.open(path);
    if (reader) 
    {
        reader >> value;
        reader.close();
    }
    else info.m_err = true;
    reader.clear();
    return value;
}

#define READ_QUEUE(i, c, d) lutils.read_sysfs((i), "/sys/block/"+(std::string)(d)+"/queue/"#c)

DiskInfo::DiskInfo(const char *string) : m_devname(std::string(string)), m_err(false)
{
}

DiskInfo DiskInfo::AsPath(const char *path)
{
    const std::string pref = "/dev/";
    std::string spath = (std::string)path;
    std::string sdevname = "";
    if (spath.rfind(pref, 0) == 0)
    {
        sdevname = spath.substr(pref.size());
        std::cout <<sdevname.c_str() << "\n";
    }
    return DiskInfo(sdevname.c_str());
}

DiskInfo DiskInfo::AsDevName(const char *devname)
{
    return DiskInfo(devname);
}

void DiskInfo::GetInfo()
{
    LinuxDiskHelperUtils lutils;
    logical_sector_size = READ_QUEUE(*this, logical_block_size, m_devname);
    physical_sector_size = READ_QUEUE(*this, physical_block_size, m_devname);
    min_io_size = READ_QUEUE(*this, minimum_io_size, m_devname);
    best_io_size = READ_QUEUE(*this, optimal_io_size, m_devname);
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
}
