#include <iostream>
#include <disk_io.hpp>
#include <error.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: disko [N/A]" << std::endl;
        return 1;
    }

    ErrorManager err_man;

    std::cout << "Path: " << argv[1] << std::endl;
    
    DiskInfo info(argv[1], *err_man.SpawnChannel("disk_info"));
    DiskIO fio(info, *err_man.SpawnChannel("disk_io"));
    info.PrintInfo();
    
    err_man.UnwindErrorStream();
    if (err_man.GetQuitCount() > 0) return 1;

    return 0;
}