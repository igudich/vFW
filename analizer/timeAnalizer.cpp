#include <iostream>
#include "statistics.h"
#include <sstream>
#include <string>

int main(int argc, char** argv)
{
    if(argc < 1)
        std::cout << "Not enough arguments" << std::endl;
    std::string dName(argv[1]);


    timeStatistics st(dName);
    st.calculate();
    st.write("stat.dat");

	return 0;
} 
