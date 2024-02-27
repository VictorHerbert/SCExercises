
#include <systemc.h>

SC_MODULE(Module){
private:
    ModuleComponent component;
    unsigned int cnt;

    sc_in<bool> in;
    sc_out<bool> out;

    sc_signal<bool> A;
    sc_signal<bool> B;
    sc_signal<bool> Z;

    
    sc_fifo<unsigned int> fifo;

    void method(){ // Methods cannot have wait inside
        out.write(!in.read());
    }

    void thread(){
        while (condition){
            wait(15, SC_NS);
        }
        sc_stop()
    }

public:
    SC_CTOR(Module) : component("component")
    {
        n1.A.bind(A);
        n1.B.bind(B);
        n1.Z.bind(Z);

        SC_METHOD(process); // Suitable for combinational logic
        SC_THREAD(thread);  // Suitable for sequential logic
        sensitive << A << B << Z;
    }

}