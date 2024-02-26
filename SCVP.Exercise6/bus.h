#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <systemc.h>
#include <tlm.h>

class bus : sc_module,
            tlm::tlm_bw_transport_if<>,
            tlm::tlm_fw_transport_if<>
{
public:
    tlm::tlm_initiator_socket<> iSocket[2];
    tlm::tlm_target_socket<> tSocket[2];

    SC_CTOR(bus)
    {
        tSocket[0].bind(*this);
        tSocket[1].bind(*this);
        iSocket[0].bind(*this);
        iSocket[1].bind(*this);
    }

    void b_transport(
        tlm::tlm_generic_payload &trans,
        sc_time &delay)
    {
        delay = delay + sc_time(40, SC_NS);
        if (trans.get_address() < 512)
        {
            iSocket[0]->b_transport(trans, delay);
        }
        else if (trans.get_address() < 1023)
        {
            trans.set_address(trans.get_address() - 512);
            iSocket[1]->b_transport(trans, delay);
        }
    }

    // Dummy method:
    void invalidate_direct_mem_ptr(
        sc_dt::uint64 start_range,
        sc_dt::uint64 end_range)
    {
    }
    // Dummy method:
    tlm::tlm_sync_enum nb_transport_bw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &delay)
    {
        return tlm::TLM_ACCEPTED;
    }

    // Dummy method
    virtual tlm::tlm_sync_enum nb_transport_fw(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_phase &phase,
        sc_time &delay)
    {
        return tlm::TLM_ACCEPTED;
    }
    // Dummy method
    bool get_direct_mem_ptr(
        tlm::tlm_generic_payload &trans,
        tlm::tlm_dmi &dmi_data)
    {
        return false;
    }
    // Dummy method
    unsigned int transport_dbg(
        tlm::tlm_generic_payload &trans)
    {
        return 0;
    }
};

#endif // BUS_H
