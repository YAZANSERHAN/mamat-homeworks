#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"
#include "string-array.h"

const int ERROR = -1;
const int ONE = 1;

int check_args(int argc, char** argv);

int main(int argc, char** argv) {
    if (check_args(argc, argv)) {
        return ERROR;
    }

    String input_string = String(argv[ONE]);
    input_string = input_string.trim();

    StringArray split_result = input_string.split("=,");

    if (split_result.size() < 2) {
        return ERROR;
    }

    String key = split_result[0];
    String value = split_result[1];

    if (key == "src-port") {
        port SP("src-port");
        SP.set_value(value);
        parse_input(SP);
    } else if (key == "src-ip") {
        ip SI("src-ip");
        SI.set_value(value);
        parse_input(SI);
    } else if (key == "dst-port") {
        port DP("dst-port");
        DP.set_value(value);
        parse_input(DP);
    } else if (key == "dst-ip") {
        ip DI("dst-ip");
        DI.set_value(value);
        parse_input(DI);
    }

    return 0;
}



int check_args(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filter-string>" << std::endl;
        return -1; // Return error code
    }
    return 0;
}