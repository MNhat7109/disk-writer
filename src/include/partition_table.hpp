#pragma once
#include <cstdint>
#include <vector>

class DiskIO;

struct PartitionTableEntry;

class PartitionTable
{
public:
    PartitionTable(DiskIO& io);

    void (*CreateEntry)(uint64_t lba_start, uint64_t length);
    void (*DeleteEntry)(uint32_t pos);
    void (*InitTableExtended)();
private:
    
    void Identify();
    void LoadExtendedOps();
    DiskIO& m_io;
    int m_type;
    uint8_t uuid[16];
    std::vector<PartitionTableEntry> entries;
};

struct PartitionTableEntry
{
    uint8_t uuid[16];
    uint64_t lba_start, length;
    uint8_t active;
    uint8_t extended[16];
};