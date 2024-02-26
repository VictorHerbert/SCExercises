#ifndef NAND_H
#define NAND_H

#include <systemc.h>

SC_MODULE(nand){
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    void compute(){
        Z.write(!(A.read() & B.read()));
    }

    SC_CTOR(nand){
        SC_METHOD(compute);
        sensitive << A << B;
    }

};

#endif
