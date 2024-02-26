#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(Transition){

    sc_port<PlaceInterface, N, SC_ALL_BOUND> in;
    sc_port<PlaceInterface, M, SC_ALL_BOUND> out;
    sc_port<PlaceInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;

    SC_CTOR(Transition){}

    void fire(){
        bool tokenFull = true;
        bool tokenInhibit = false;

        for (int i = 0; i < N and tokenFull; i++)
            tokenFull &= in[i]->testTokens();
        
        if(tokenFull)
            for (int i = 0; i < L and not tokenInhibit; i++)
                tokenInhibit |= inhibitors[i]->testTokens();

        if(tokenFull and not tokenInhibit){
            std::cout << this->name() << ": Fired" << std::endl;
            
            for (int i = 0; i < N; i++)
                in[i]->removeTokens();
            for (int j = 0; j < M; j++)
                out[j]->addTokens();
        }
        else
            std::cout << this->name() << ": NOT Fired" << std::endl; 
            
   
    }

};

#endif // TRANSITION_H
