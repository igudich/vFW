#include "chain.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cassert>

chain::chain()
{

}

double chain::getLength()
{
    double res = 0;
    for(int i = 0; i < positions.size(); ++i)
        for(int j = i+1; j < positions.size(); ++j)
            res = std::max(res, vect(positions[i], positions[j]).length());
    return res;
}

void chain::read(std::ifstream& fin)
{
    std::string s;
    std::stringstream ss;

    std::getline(fin, s);
    int i = 0;
    while(s[0] != '*' && fin.good())
    {
        if(i + 1  > positions.size())
            positions.resize(i + 1);
        ss << s;
        if(!s.empty())
        {
            ss >> positions[i].x >> positions[i].y >> positions[i].z;
            ++i;
        }
        std::getline(fin, s);
    }
}

