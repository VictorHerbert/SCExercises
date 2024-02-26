#include <systemc.h>

#include "stim.h"
#include "exor.h"
#include "mon.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;
    sc_clock clk("Clk", 10, SC_NS);

    stim Stim1("Stimulus");
    Stim1.clk(clk);
    Stim1.A(sigA);
    Stim1.B(sigB);

    exor DUT("exor");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Z(sigZ);

    Monitor mon("Monitor");
    mon.clk(clk);
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);
    
    
    sc_trace_file *wf = sc_create_vcd_trace_file("trace");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, sigA, "a");
    sc_trace(wf, sigB, "b");
    sc_trace(wf, sigZ, "Z");

    sc_start();  // run forever

    sc_close_vcd_trace_file(wf);


    return 0;
}
