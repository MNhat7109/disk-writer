#include <partition_table.hpp>
#include <plugin/partition_table_client.hpp>
#include <error.hpp>

#define PLUGIN_MAX 64

#define ASSERT_EXEC(_xf, ...) \
do { \
    if (!m_table_ops||!m_table_ops->_xf) \
    { \
        SetErrorNotImplemented(); \
    } \
    else (m_table_ops->_xf)(*this, ##__VA_ARGS__);\
} while (0)

PartitionTable::PartitionTable(DiskIO &io, ErrorChannel& channel) : 
m_io(io), 
m_type(-1), 
m_table_ops(nullptr), 
m_plugins({}),
m_err_channel(channel)
{
    m_plugins.reserve(PLUGIN_MAX);
}

void PartitionTable::RegisterPlugin(const PartitionTablePlugin *plugin)
{
    if (m_plugins.size() >= PLUGIN_MAX) return; //TODO
    m_plugins.push_back(plugin);
}

void PartitionTable::DetectPlugin()
{
    for (const PartitionTablePlugin* plug : m_plugins)
    {
        int status=-1;
        if (!plug->probe)
        {
            m_err_channel.Swear("Probe function implementation not found. Skipping...");
            continue;
        }

        if ((status = plug->probe(m_io)) != PROBE_MATCH_FULL)
        {
            m_err_channel.Swear("Probing returns only partial matching. Finding better matches...");
            continue;
        }

        PopulateItems(plug);
        break;
    }

    // Cleanup
}

void PartitionTable::LoadOps(const PartitionTableOps *ops)
{
    m_table_ops = ops;
}

void PartitionTable::PopulateItems(const PartitionTablePlugin* plugin)
{
    LoadOps(plugin->ops);
}

void PartitionTable::SetErrorNotImplemented()
{
    m_err_channel.Scream("Feature not implemented yet");
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
