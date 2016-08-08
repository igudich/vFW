#include "params.h"
#include <iostream>

using std::endl;
using std::cout;

int main() {
    params.read_from_file("params.txt");

    cout << "dt = " << params.dt << endl;
    cout << "ns = " << params.ns << endl;
    cout << "nfac = " << params.nfac << endl << endl;

    cout << "N = " << params.N << endl;
    cout << "kT = " << params.kT << endl;
    cout << "R = " << params.R << endl;
    cout << "d = " << params.d << endl << endl;

    cout << "uvdw = " << params.uvdw << endl;
    cout << "uspr = " << params.uspr << endl;
    cout << "alpha = " << params.alpha << endl << endl;

    cout << "srat = " << params.srat << endl;
    cout << "erat = " << params.erat << endl << endl;

    cout << "nu = " << params.nu << endl;
    cout << "gamma = " << params.gamma << endl;
    cout << "D = " << params.D << endl << endl;

    cout << "mno = " << params.mno << endl;
    cout << "kspr = " << params.kspr << endl;
    cout << "kvdw = " << params.kvdw << endl;

    return 0;
}
