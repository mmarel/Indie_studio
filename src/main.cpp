//
// Author: Marwane Khsime 
// Date: 2017-05-03 01:50:31 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-03 01:50:31
//

#include <iostream>

#include "Exception/exception.hpp"
#include "Common/common.hpp"

int main() {

    #if defined __linux__
        if (helper::Helper::get().getEnvVariable("DISPLAY") != ":0")
            std::cerr << "The DISPLAY environment variable is not set correctly." << std::endl;
    #endif

    return EXIT_SUCCESS;
}
