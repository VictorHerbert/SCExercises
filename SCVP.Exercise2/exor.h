#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>

#include "nand.h"

SC_MODULE(exor){
public:
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;
    
    SC_CTOR(exor) :
        a("a"), b("b"), c("c"), d("d")
    {
        a.A.bind(A); a.B.bind(B); a.Z.bind(h1);
        c.A.bind(A); c.B.bind(h1); c.Z.bind(h2);
        b.A.bind(h1); b.B.bind(B); b.Z.bind(h3);
        d.A.bind(h2); d.B.bind(h3); d.Z.bind(Z);

        sensitive << A << B;
    }

private:
    nand a, b, c, d;
    sc_signal<bool> h1, h2, h3;
};

#endif // EXOR_H
