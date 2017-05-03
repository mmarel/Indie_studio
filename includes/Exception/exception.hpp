//
// Author: Marwane Khsime 
// Date: 2017-05-03 00:59:29 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-05-03 00:59:29
//

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <string>
#include <exception>


namespace project
{

    ///\class Error
    ///\brief Class inheriting from std exception.
    ///
    class Error : public std::exception {
        
        protected:
            std::string _message;   ///< Brief Contains the error message
        
        public:
            Error(const std::string &message) noexcept : _message(message) {};
            Error() noexcept;
            virtual ~Error() noexcept {};

            virtual const char *what() const noexcept { return this->_message.c_str(); };

    };
}

# endif // EXCEPTION_HPP
