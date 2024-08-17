#ifndef IP_H
#define IP_H

#include "string.h"



class ip : public GenericField{
    String ipType;
    int subnet_mask;
    int ruleIP[4];

    public: 

    ip(String ipType); // constructor
    bool match(const GenericString &packet) const override;
    bool set_value(String value);
    
};

#endif