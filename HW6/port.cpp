#include "port.h"
#include <iostream>
#include <stddef.h>
#include "string-array.h"  // Ensure this includes the full definition of StringArray

const int ONE = 1;
const int TWO = 2;
const int MAX = 65535;

// Constructor
port::port(String portType) : GenericField(), portType(portType), minPort(0), maxPort(MAX) {}

// Set the value for the port range
bool port::set_value(String value) {
    // Split the input value using '-' as the delimiter
    StringArray thisString = value.split("-");

    // Check if the split resulted in exactly two parts
    if (thisString.size() == 2) {
        int min = thisString[0].to_integer();
        int max = thisString[1].to_integer();

        // Ensure the min and max are within the valid port range and min is less than or equal to max
        if (min >= 0 && max <= MAX && max >= min) {
            minPort = min;
            maxPort = max;
            return true;
        }
    }
    
    // If the input is invalid, return false
    return false;
}

// Auxiliary match function for port
bool port::aux_match(String value) const {
    int port_num = (value.trim()).to_integer();
    return (minPort <= port_num && maxPort >= port_num);
}

// Match function for the port
bool port::match(const GenericString &packet) const {
    // Tokenize the packet string based on delimiters
    StringArray splitResult = packet.split("=, ");

    // Ensure there are elements in the result
    if (splitResult.size() == 0) {
        return false;
    }

    // Iterate through the split results to find the relevant port type
    for (size_t i = 0; i < splitResult.size(); i += TWO) {
        if (portType == splitResult[i]) {
            // Perform matching based on the port range
            if (i + ONE < splitResult.size()) {
                // Ensure the port is within the specified range
                if (aux_match(splitResult[i + ONE])) {
                    return true;
                }
            }
        }
    }

    return false;
}
