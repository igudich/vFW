#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>
#include <vector>


class timeStatistics
{
    int nTimes;
    std::vector<std::string> files;
    std::string dirName;
    void makeFiles();
public:
    std::vector<double> stat;
    timeStatistics(const std::string& dn);
    void calculate();
    void write(const std::string& fname);
};

#endif // STATISTICS_H
