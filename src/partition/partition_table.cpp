#include <partition_table.hpp>

enum PartitionTableType
{
    PT_TYPE_MBR,
    PT_TYPE_GPT,
    PT_TYPE_UNKNOWN
};

PartitionTable::PartitionTable(DiskIO &io) : m_io(io), m_type(PT_TYPE_UNKNOWN)
{
}

void PartitionTable::LoadOps(PartitionTableOps& ops)
{
    table_ops = ops;
}
