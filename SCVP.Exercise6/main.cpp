#include <iostream>
#include <iomanip>
#include <systemc.h>

#include "memory.h"
#include "processor.h"
#include "bus.h"


int sc_main (int, char **)
{
    processor cpu[] = {
        processor("cpu0", "stimuli1.txt", sc_time(1, SC_NS)),
        processor("cpu1", "stimuli2.txt", sc_time(1, SC_NS))
    };

    bus bus("bus");

    memory<512> mem[] = {
        memory<512>("memory0"),
        memory<512>("memory1")
    };
        
    bus.tSocket[0](cpu[0].iSocket); bus.tSocket[1](cpu[1].iSocket);
    bus.iSocket[0](mem[0].tSocket); bus.iSocket[1](mem[1].tSocket);

    //cpu0.iSocket.bind(memory0.tSocket);

    std::cout << std::endl << "Name "
              << std::setfill(' ') << std::setw(10)
              << "Time" << " "
              << std::setfill(' ') << std::setw(5)
              << "CMD" << "   "
              << std::setfill(' ') << std::setw(8)
              << "Address"
              << "   " << std::hex
              << std::setfill(' ') << std::setw(8)
              << "Data"
              << " " << std::endl
              << "-------------------------------------------"
              << std::endl;

    sc_start();

    std::cout << std::endl;
    return 0;
}
