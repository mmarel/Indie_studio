//
// Author: Maud Marel 
// Date: 2017-06-17 18:34:07 
//

#ifndef SCORE_HPP_
# define SCORE_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace indie
{
    class   Score
    {
        std::vector<int>            _scores;
        std::vector<std::string>    _names;

    public:
        Score();
        ~Score();
        int get_bigger_score();
        void add_score(const std::string &, int);
    };
}

#endif /* !SCORE_HPP_ */