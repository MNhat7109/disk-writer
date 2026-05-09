#include <partition_table.hpp>

enum PartitionTableType
{
    PT_TYPE_MBR,
    PT_TYPE_GPT,
    PT_TYPE_UNKNOWN
};

#define ASSERT_EXEC(_xf, ...) \
do { \
    if (!m_table_ops||!m_table_ops->_xf) \
    { \
        SetErrorNotImplemented(); \
    } \
    else (m_table_ops->_xf)(*this, ##__VA_ARGS__);\
} while (0)

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

void PartitionTable::SetErrorNotImplemented()
{
    
}

void PartitionTable::CreatePartEntry(uint64_t lba_start, uint64_t length)
{
    ASSERT_EXEC(CreatePartEntry, lba_start, length);
}

void PartitionTable::DeletePartEntry(uint32_t pos)
{
    ASSERT_EXEC(DeletePartEntry, pos);
}

void PartitionTable::InitTable()
{
    ASSERT_EXEC(InitTable);
}

void PartitionTable::SpawnTable()
{
    ASSERT_EXEC(SpawnTable);
}

void PartitionTable::PopulateTable()
{
    ASSERT_EXEC(PopulateTable);
}

void PartitionTable::PrintEntries()
{
    ASSERT_EXEC(PrintEntries);
}

void PartitionTable::PrintGeneralInfo()
{
    ASSERT_EXEC(PrintGeneralInfo);
}

void PartitionTable::PrintFull()
{
    ASSERT_EXEC(PrintFull);
}
