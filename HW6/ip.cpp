#include "ip.h"
#include <iostream>
#include <stddef.h>
#include "string.h"
#include "string-array.h"  // Include the full definition of StringArray

const int MAX = 256;
const int SLASH = 1; // There is one slash in the IP address
const int BYTES = 8;
const int POINTS = 4;
const int ZERO = 0;
const int WORD = 32;

// Constructor
ip::ip(String ipType) : ipType(ipType), subnet_mask(0) {
    for (int i = 0; i < POINTS; i++) {
        ruleIP[i] = 0;
    }
}


// Set value method
bool ip::set_value(String value) {
    StringArray parts = value.split("/");
    if (parts.size() != 2) {
        return false;
    }

    String ipPart = parts[0];
    subnet_mask = parts[1].to_integer();

    if (subnet_mask < ZERO || subnet_mask > WORD) {
        return false;
    }

    StringArray ipParts = ipPart.split(".");
    if (ipParts.size() != POINTS) {
        return false;
    }

    for (int i = 0; i < POINTS; ++i) {
        int part = ipParts[i].to_integer();
        if (part < ZERO || part >= MAX) {
            return false;
        }
        ruleIP[i] = part;
    }

    return true;
}

bool ip::match(const GenericString &packet) const {
    String fieldToMatch;  
    StringArray packetParts = packet.split(", ");
    
    for (size_t i = 0; i < packetParts.size(); i++) {
        String fullPart = packetParts[i];
        StringArray IP_part = fullPart.split("=");

        if (IP_part.size() == 2 && IP_part[0] == ipType) {
            fieldToMatch = IP_part[1];
            
            if (fieldToMatch.is_empty()) {
                return false;
            }

            StringArray parts = fieldToMatch.split(".");
            if (parts.size() != POINTS) {
                return false;
            }

            int packetIP[POINTS];
            for (int j = 0; j < POINTS; j++) {
                int part = parts[j].to_integer();
                if (part >= MAX || part < ZERO) {
                    return false;
                }
                packetIP[j] = part;
            }

            int mask = (subnet_mask == 0) ? 0 : 0xFFFFFFFF << (32 - subnet_mask);
            int ruleIP_int = (ruleIP[0] << 24) | (ruleIP[1] << 16) | (ruleIP[2] << 8) | ruleIP[3];
            int packetIP_int = (packetIP[0] << 24) | (packetIP[1] << 16) | (packetIP[2] << 8) | packetIP[3];

            return (ruleIP_int & mask) == (packetIP_int & mask);
        }
    }
    return false;
}

