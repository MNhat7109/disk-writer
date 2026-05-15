#pragma once
#include <cstdint>

class DiskIO;
struct PartitionTableOps;

enum ProbeResult
{
    PROBE_MATCH_FULL,
    PROBE_MATCH_PARTIAL,
    PROBE_MATCH_NONE
};

struct PartitionTablePlugin
{
    const char* plugname;
    struct
    {
        uint8_t major;
        uint8_t minor;
    } version;
    int (*probe)(DiskIO& io);
    const PartitionTableOps* ops;
};