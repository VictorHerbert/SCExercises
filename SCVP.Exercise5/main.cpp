#include <iostream>
#include <systemc.h>

#include "kpn.h"

int sc_main(int, char**)
{
    sc_signal<unsigned int> output;

    kpn kahn("kpn");
    kahn.e(output);

    sc_start();
    return 0;
}
