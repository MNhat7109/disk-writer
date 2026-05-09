#pragma once
#include <cstdint>
#include <vector>

class DiskIO;
class PartitionTable;

struct PartitionTableEntry;
struct PartitionTableOps;

class PartitionTable
{
public:
    PartitionTable(DiskIO& io);

    PartitionTableOps& table_ops;
    DiskIO& m_io;
    std::vector<PartitionTableEntry> m_entries;
private:
    void Identify();
    void LoadOps(PartitionTableOps& ops);
    int m_type;
    uint8_t uuid[16];
};

struct PartitionTableOps
{
    void (*CreatePartEntry)(PartitionTable&, uint64_t lba_start, uint64_t length);
    void (*DeletePartEntry)(PartitionTable&, uint32_t pos);
    void (*InitTable)(PartitionTable&);
    void (*SpawnTable)(PartitionTable&);
    void (*PopulateTable)(PartitionTable&);
    void (*PrintEntries)(PartitionTable&);
    void (*PrintGeneralInfo)(PartitionTable&);
    void (*PrintFull)(PartitionTable&);
};

struct PartitionTableEntry
{
    uint8_t uuid[16];
    uint64_t lba_start, length;
    uint8_t active;
    uint8_t extended[16];
};