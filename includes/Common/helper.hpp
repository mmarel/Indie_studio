//
// Author: Marwane Khsime 
// Date: 2017-05-03 15:28:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-03 15:28:57
//

#ifndef HELPER_HPP
# define HELPER_HPP

#include <string>
#include <sstream>
#include <vector>

namespace helper {

    class Helper
    {

        private:
            Helper() {}

        public:
            Helper(const Helper &)  = delete;
            void operator=(const Helper &)  = delete;

            static Helper& Get() noexcept {
                static Helper    instance;

                return instance;
            }

            std::string getEnvVariable(const std::string &key) noexcept {
                char * val = getenv( key.c_str() );
                return val == NULL ? std::string("") : std::string(val);
            }
    };

}
 
# endif // HELPER_HPP