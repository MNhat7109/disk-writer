#include <disk_io.hpp>

#define SECTOR_SIZE 512

DiskIO::DiskIO(const char *path) : diskInfo(DiskInfo::AsPath(path))
{
    f.open(path, std::ios::in | std::ios::out | std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open file");

    diskInfo.GetInfo();
    // TODO
}

int DiskIO::Read(uint64_t lba, uint32_t sector_count, void *buf)
{
    size_t offset = lba*diskInfo.logical_sector_size;
    size_t n = sector_count*SECTOR_SIZE; // TODO
    f.seekg(offset, std::ios::beg);
    f.read((char*)buf, n);
    f.clear();
    f.seekg(0, std::ios::beg);
    return 0;
}

int DiskIO::Write(uint64_t lba, uint32_t sector_count, void *buf)
{
    size_t offset = lba*diskInfo.logical_sector_size;
    size_t n = sector_count*SECTOR_SIZE;  // TODO
    f.seekp(offset, std::ios::beg);
    f.write((char*)buf, n);
    f.clear();
    f.seekp(0, std::ios::beg);
    return 0;
}

void DiskIO::Dump()
{
}

DiskIO::~DiskIO()
{
    f.close();
}