#include <disk_io.hpp>
#include <error.hpp>

#define SECTOR_SIZE 512

DiskIO::DiskIO(DiskInfo& diskInfo, ErrorChannel& channel) : 
m_diskInfo(diskInfo),
m_path(m_diskInfo.GetDevicePath()),
m_err_channel(channel)
{
    Initialize();
}

void DiskIO::Initialize()
{
    m_io.open(m_path, std::ios::in | std::ios::out | std::ios::binary);
    if (!m_io) m_err_channel.ThatsItIQuit("Cannot open disk");

    m_diskInfo.GetInfo();
    if (m_diskInfo.GetError()) m_err_channel.ThatsItIQuit("Error getting info from disk");
}

int DiskIO::Read(uint64_t lba, uint32_t sector_count, void *buf)
{
    if (m_err_channel.HasError()) return -1;

    size_t offset = lba*m_diskInfo.logical_sector_size;
    size_t n = sector_count*m_diskInfo.logical_sector_size;
    m_io.seekg(offset, std::ios::beg);

    size_t max_read_size = m_diskInfo.best_io_size?m_diskInfo.best_io_size:m_diskInfo.min_io_size;
    while (n)
    {
        size_t chunk_size = std::max(max_read_size, n);

        m_io.read((char*)buf, chunk_size);
        if (!m_io.good())
        {
            m_err_channel.Swear("Read error occurred");
            return -1;
        }

        buf = (uint8_t*)buf+chunk_size;
        n-=chunk_size;
    }

    m_io.clear();
    m_io.seekg(0, std::ios::beg);
    return 0;
}

int DiskIO::Write(uint64_t lba, uint32_t sector_count, void *buf)
{
    if (m_err_channel.HasError()) return -1;

    size_t offset = lba*m_diskInfo.logical_sector_size;
    size_t n = sector_count*m_diskInfo.logical_sector_size;
    m_io.seekp(offset, std::ios::beg);

    size_t max_write_size = m_diskInfo.best_io_size?m_diskInfo.best_io_size:m_diskInfo.min_io_size;
    while (n)
    {
        size_t chunk_size = std::max(max_write_size, n);
        if (!m_io.good())
        {
            m_err_channel.Swear("Write error occurred");
            return -1;
        }

        m_io.write((char*)buf, chunk_size);
        buf = (uint8_t*)buf+chunk_size;
        n-=chunk_size;
    }

    m_io.clear();
    m_io.seekp(0, std::ios::beg);
    return 0;
}

void DiskIO::PrintDiskInfo()
{
    if (m_err_channel.HasError()) return;

    m_diskInfo.PrintInfo();
}

void DiskIO::Dump()
{
    if (m_err_channel.HasError()) return;
}

DiskIO::~DiskIO()
{
    m_io.close();
}

