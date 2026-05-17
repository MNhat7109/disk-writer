#pragma once
#include <cstdint>
#include <vector>

class DiskIO;
class PartitionTable;
class ErrorChannel;

struct PartitionTableEntry;
struct PartitionTableOps;

struct PartitionTablePlugin;

class PartitionTable
{
public:
    PartitionTable(DiskIO& io, ErrorChannel& channel);

    void RegisterPlugin(const PartitionTablePlugin* plugin);
    void DetectPlugin();

    void CreatePartEntry(uint64_t lba_start, uint64_t length);
    void DeletePartEntry(uint32_t pos);
    void InitTable();
    void SpawnTable();
    void PopulateTable();
    void PrintEntries();
    void PrintGeneralInfo();
    void PrintFull();

    DiskIO& m_io;
    std::vector<PartitionTableEntry> m_entries;
    ErrorChannel& m_err_channel;
private:
    const PartitionTableOps* m_table_ops;
    std::vector<const PartitionTablePlugin*> m_plugins;
    int m_type;
    uint8_t uuid[16];

private:
    void LoadOps(const PartitionTableOps* ops);
    void PopulateItems(const PartitionTablePlugin* plugin);
    void SetErrorNotImplemented();
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