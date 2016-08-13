#ifndef CHAIN_H
#define CHAIN_H

#include "../new_code/vect.h"
#include <vector>
#include <fstream>


class chain
{
public:
    std::vector<vect> positions;

    chain();
    double getLength();
    void read(std::ifstream& fin);
};

#endif // CHAIN_H
