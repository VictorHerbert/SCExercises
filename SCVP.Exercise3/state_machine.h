#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(stateMachine)
{
public:
    sc_in<bool> clk;
    sc_in<char> input;
    
    SC_CTOR(stateMachine){
        SC_METHOD(process);
        sensitive << clk.pos() << input;
        occurenceCount = 0;
        globalCounter = 0;
        dont_initialize();
    }

private:
    enum State {Start, G, GA, GAA, GAAG};
    State state;

    int occurenceCount;
    int globalCounter;
    int ocurrenceCurrent;

    void process(){
        globalCounter++;
        std::vector<std::string> stateNames = {"Start", "G", "GA", "GAA", "GAAG"};

        std::cout << sc_time_stamp()  << "\t" << input << "\t" << stateNames[state] << "\t" << std::endl;

        switch (state){
        case Start:
            if(input.read() == 'G'){
                ocurrenceCurrent = globalCounter;
                state = G;
            }
            break;
        case G:
            switch (input.read()){
            case 'A':
                state = GA;
                break;
            case 'G':
                state = G;
                ocurrenceCurrent = globalCounter;
                break;
            default: // input  = C|T
                state = Start;
                break;
            }
            break;
        case GA:
            switch (input.read()){
            case 'A':
                state = GAA;
                break;
            case 'G':
                state = G;
                break;
            default: // input  = C|T
                state = Start;
                break;
            }
            break;
        case GAA:
            switch (input.read()){
            case 'G':
                state = GAAG;
                break;
            case 'A':
                state = GAA;
                break;
            default: // input  = C|T
                state = Start;
                break;
            }
            break;
        case GAAG:
            std::cout << "\n" 
                << ++occurenceCount << " instances of GA{2,}G found" << "\n"
                << "Last at " << ocurrenceCurrent << "-" << globalCounter << "\n"
                << std::endl;
            switch (input.read()){
            case 'G':
                state = G;
                break;
            default: // input  = C|T
                state = Start;
                break;
            }
            break;
        }
        
    }
};

#endif // STATE_MACHINE_H


