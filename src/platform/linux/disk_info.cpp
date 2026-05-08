#include <disk_info.hpp>
#include <iostream>

#define INVALID_VALUE (uint64_t)-1
std::ifstream reader;

#define SECTOR_SIZE 512

class LinuxDiskHelperUtils
{
public:
    uint64_t read_sysfs(DiskInfo& info, std::string path);
};


uint64_t LinuxDiskHelperUtils::read_sysfs(DiskInfo& info, std::string path)
{
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
#define READ_SIZE(i, d) lutils.read_sysfs((i), "/sys/block/"+(std::string)(d)+"/size")

void DiskInfo::GetInfo()
{
    LinuxDiskHelperUtils lutils;
    logical_sector_size = READ_QUEUE(*this, logical_block_size, m_devname);
    physical_sector_size = READ_QUEUE(*this, physical_block_size, m_devname);
    min_io_size = READ_QUEUE(*this, minimum_io_size, m_devname);
    best_io_size = READ_QUEUE(*this, optimal_io_size, m_devname);
    total_sector_count = READ_SIZE(*this, m_devname)*SECTOR_SIZE/logical_sector_size;
}


void DiskInfo::ParsePath()
{
    const std::string pref = "/dev/";
    std::string spath = (std::string)m_devpath;
    if (m_devpath.rfind(pref, 0) == 0)
    {
        m_devname = m_devpath.substr(pref.size());
        std::cout <<m_devname << "\n";
    }
}