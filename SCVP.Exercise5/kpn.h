#ifndef KPN_H
#define KPN_H

#include <systemc.h>

SC_MODULE(kpn)
{
private:
    sc_fifo<unsigned int> a,b,c,d;
    
    void add();
    void split();
    void delay();

public:
    sc_out<unsigned int> e;

    SC_CTOR(kpn) :
        a(10), b(10), c(10), d(10)
    {
        b.write(1);
        c.write(0);
        
        SC_THREAD(split);
        SC_THREAD(add);
        SC_THREAD(delay);
        //sensitive << a << b << c << d;
    }
};

#endif // KPN_H
