#ifndef PORT_H
#define PORT_H


#include "string.h"

const int SHORT=2;
class port : public GenericField{
    String portType;
    int maxPort;
    int minPort;

public:
    port(String portType);
    bool match(const GenericString &packet) const override;
    bool set_value(String value) ;
    bool aux_match(String string) const;
    

};

#endif 