#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

class PlaceInterface : virtual public sc_interface {
public:
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;  
};

template<unsigned int Win = 1, unsigned int Wout = 1>
class Place : public PlaceInterface {
private:
    unsigned int tokens;
public:
    Place(int _tokens) : tokens(_tokens) {}

    void addTokens(){tokens += Win;}
    void removeTokens(){tokens -= Wout;}
    bool testTokens(){return tokens >= Wout;}
};

#endif // PLACE_H
