#pragma once
#include <disk_io.hpp>
#include <cstdint>
#include <vector>

struct PartitionEntry
{
    uint64_t lba_start;
    uint64_t sector_count;
};

class DiskLayout
{
public:
    DiskLayout(DiskIO& io);
    void Identify();
    void PrintTable();
    void PrintGeneralInfo();
    void PrintFullLayout();
private:
    DiskIO& m_io;
    std::vector<PartitionEntry> entries;
};