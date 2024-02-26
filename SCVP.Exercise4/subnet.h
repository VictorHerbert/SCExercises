#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"


// Toplevel:
SC_MODULE(Subnet){

    Transition<1,1,1> ACT;
    Transition<1,1> RD, PRE, WR;
    Place<1,1> ACTIVE;

    sc_port<PlaceInterface> in, out;

    SC_CTOR(Subnet) :
        ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), ACTIVE(0)
    {
        ACT.in(in);         ACT.out(ACTIVE);  ACT.inhibitors(ACTIVE);
        RD.in(ACTIVE);      RD.out(ACTIVE);
        PRE.in(ACTIVE);     PRE.out(in);
        WR.in(ACTIVE);      WR.out(ACTIVE);
    }

};

#endif // SUBNET_H
