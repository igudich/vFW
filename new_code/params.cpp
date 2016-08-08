#include "params.h"
#include <fstream>
#include <sstream>
#include <cmath>

using std::ifstream;
using std::stringstream;
using std::string;

parameters::parameters() {}

template<typename param_type>
static void read_param(ifstream& fin, param_type& p) {
    string s;
    stringstream ss;

    std::getline(fin, s);
    ss << s;
    ss >> p;
}

void parameters::read_from_file(string filename) {
    ifstream fin(filename.c_str());

    read_param(fin, dt);
    read_param(fin, ns);
    read_param(fin, nfac);

    read_param(fin, N);
    read_param(fin, kT);
    read_param(fin, R);
    
    d = 2 * R;

    read_param(fin, uvdw);
    read_param(fin, uspr);
    read_param(fin, alpha);

    read_param(fin, srat);
    read_param(fin, erat);
    srat /= RATE_NORM;
    erat /= RATE_NORM;

    read_param(fin, nu);
    gamma = 6 * M_PI * nu * R;
    D = kT / gamma;

    mno = std::sqrt(2 * gamma * kT / dt);
    kspr = (uspr / (2 * R * R)) * kT;
    kvdw = uvdw * kT;

    fin.close();
}
