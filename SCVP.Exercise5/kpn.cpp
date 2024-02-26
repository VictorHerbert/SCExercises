#include <unistd.h>
#include <systemc.h>

#include "kpn.h"

void kpn::add(){
    while (true)
        b.write(a.read() + c.read());
}

void kpn::split(){
    int i = 10;
    while(i--){
        int fifo_top = b.read();
        a.write(fifo_top);
        d.write(fifo_top);
        e.write(fifo_top);

        std::cout << "@" << sc_delta_count() << " E -> " << fifo_top << std::endl;
    }
    
    sc_stop();
}

void kpn::delay(){
    while (true)    
        c.write(d.read());
}
