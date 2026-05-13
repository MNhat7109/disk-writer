#include <partition_table.hpp>

enum PartitionTableType
{
    PT_TYPE_MBR,
    PT_TYPE_GPT,
    PT_TYPE_UNKNOWN
};

PartitionTable::PartitionTable(DiskIO &io) : m_io(io), m_type(PT_TYPE_UNKNOWN), m_table_ops(nullptr)
{
}

void PartitionTable::Identify()
{
}

void PartitionTable::LoadOps(PartitionTableOps *ops)
{
    m_table_ops = ops;
}

void PartitionTable::CreatePartEntry(uint64_t lba_start, uint64_t length){}
void PartitionTable::DeletePartEntry(uint32_t pos){}
void PartitionTable::InitTable(){}
void PartitionTable::SpawnTable(){}
void PartitionTable::PopulateTable(){}
void PartitionTable::PrintEntries(){}
void PartitionTable::PrintGeneralInfo(){}
void PartitionTable::PrintFull(){}
