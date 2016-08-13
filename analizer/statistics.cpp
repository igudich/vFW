#include "statistics.h"
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include "chain.h"


using namespace std;

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
        files.push_back(dir + "/" + string(dirp->d_name));

    closedir(dp);
    return 0;
}


void timeStatistics::makeFiles()
{
    getdir(dirName, files);
    auto iter = files.begin();
    while(iter != files.end())
    {
        if(iter->find(string("_coords")) == string::npos)
            files.erase(iter);
        else
            iter++;
    }
}

timeStatistics::timeStatistics(const std::string& dn) :
    dirName(dn)
{
    makeFiles();
    cout << "folder : " << dirName << endl;
}

void timeStatistics::write(const string& fname)
{
    ofstream ofstr;
    ofstr.open(fname.c_str());
    assert(ofstr.is_open());

    for(auto& it : stat)
        ofstr << it << endl;

    ofstr.close();
}

void timeStatistics::calculate()
{
    chain ch;
    string s;
    for(int i = 0; i < files.size(); ++i)
    {
        string pF = files[i];
        cout << pF << endl;
        ifstream ifstr;
        ifstr.open((pF));
        getline(ifstr, s); //skip first raw
        int iTime = 0;
        while(ifstr.good())
        {
            ch.read(ifstr);
            if(i == 0)
            {
                stat.push_back(ch.getLength());
                nTimes++;
            }
            else
            {
                if(iTime >= nTimes)
                    break;
                else
                    stat[iTime] += ch.getLength();
            }
            iTime++;
        }
        for(auto& it : stat)
            it /= files.size();
        if(i == 0)
            nTimes++;
        ifstr.close();
    }

}
