#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
SC_MODULE(Toplevel){
private:
    Subnet s1, s2;
    Place<2,2> idle;

public:    
    SC_CTOR(Toplevel) :
        s1("s1"), s2("s2"), idle(2)
    {
        s1.in(idle);    s1.out(idle);
        s2.in(idle);    s2.out(idle);

        SC_THREAD(process);
        //sensitive << t1 << t2;
    }

    void process(){
        while (true){
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.RD.fire();
            wait(10, SC_NS);
            s1.WR.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s2.PRE.fire();
            wait(10, SC_NS);
            sc_stop();
        }
    }
};

int sc_main(int, char**){
    
    Toplevel t("t");

    sc_start();

    return 0;
}
