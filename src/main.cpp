#include <iostream>
#include <disk_io.hpp>

int ret = 0;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: disko [N/A]" << std::endl;
        return 1;
    }

    std::cout << "Path: " << argv[1] << std::endl;
    
    try
    {
        DiskIO fio = DiskIO(argv[1]);
        
        fio.PrintDiskInfo();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        ret = 1;
        goto done;
    }

done:
    return ret;
}