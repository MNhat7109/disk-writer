#include <disk_io.hpp>

#define SECTOR_SIZE 512

DiskIO::DiskIO(const char *path) : diskInfo(DiskInfo::AsPath(path))
{
    f.open(path, std::ios::in | std::ios::out | std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open disk");

    diskInfo.GetInfo();
    if (diskInfo.GetError()) throw std::runtime_error("Error getting info from disk");
}

int DiskIO::Read(uint64_t lba, uint32_t sector_count, void *buf)
{
    size_t offset = lba*diskInfo.logical_sector_size;
    size_t n = sector_count*diskInfo.logical_sector_size;
    f.seekg(offset, std::ios::beg);

    size_t max_read_size = diskInfo.best_io_size?diskInfo.best_io_size:diskInfo.min_io_size;
    while (n)
    {
        size_t chunk_size = std::max(max_read_size, n);

        f.read((char*)buf, chunk_size);
        buf = (uint8_t*)buf+chunk_size;
        n-=chunk_size;
    }

    f.clear();
    f.seekg(0, std::ios::beg);
    return 0;
}

int DiskIO::Write(uint64_t lba, uint32_t sector_count, void *buf)
{
    size_t offset = lba*diskInfo.logical_sector_size;
    size_t n = sector_count*diskInfo.logical_sector_size;
    f.seekp(offset, std::ios::beg);

    size_t max_write_size = diskInfo.best_io_size?diskInfo.best_io_size:diskInfo.min_io_size;
    while (n)
    {
        size_t chunk_size = std::max(max_write_size, n);

        f.write((char*)buf, chunk_size);
        buf = (uint8_t*)buf+chunk_size;
        n-=chunk_size;
    }

    f.clear();
    f.seekp(0, std::ios::beg);
    return 0;
}

void DiskIO::PrintDiskInfo()
{
    diskInfo.PrintInfo();
}

void DiskIO::Dump()
{
}

DiskIO::~DiskIO()
{
    f.close();
}