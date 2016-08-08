#include "params.h"
#include "vwf_model.h"
#include "hydro.h"
#include "spheres_interaction.h"
#include "random_force.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    vwf_model model;
    
    parameters & params = model.params;

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
    cout << "kvdw = " << params.kvdw << endl << endl;

    model.read_positions("initial_coords_40.txt");
    model.forces.emplace_back(new spheres_interaction_force());
    model.forces.emplace_back(new hydro());
    model.forces.emplace_back(new random_force(179));

    // Main loop over time

    for (int s = 0; s < params.N; s++) {
        model.iterate();
        if (s % params.nfac == 0) {
            cout << s << endl;
        }
    }

    return 0;
}
