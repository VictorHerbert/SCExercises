#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>

template<size_t size>
class memory : sc_module, tlm::tlm_fw_transport_if<>
{
private:
    unsigned char mem[1024];

public:
    tlm::tlm_target_socket<> tSocket;

    SC_CTOR(memory) : tSocket("tSocket"){
        tSocket.bind(*this);
    }

    void b_transport(tlm::tlm_generic_payload &trans,
                     sc_time &delay)
    {
        if (trans.get_address() >= size)
        {
            SC_REPORT_FATAL(this->name(), "Out of Range");
        }
        if (trans.get_command() == tlm::TLM_WRITE_COMMAND)
        {
            memcpy(mem + trans.get_address(), // destination
                   trans.get_data_ptr(),      // source
                   trans.get_data_length());  // size
        }
        else
        {
            memcpy(trans.get_data_ptr(),      // destination
                   mem + trans.get_address(), // source
                   trans.get_data_length());  // size
        }
        delay = delay + sc_time(40, SC_NS);

        trans.set_response_status( tlm::TLM_OK_RESPONSE );
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

#endif // MEMORY_H
