#include "params.h"
#include "vwf_model.h"
#include "hydro.h"
#include "spheres_interaction.h"
#include "random_force.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

std::string get_date_string() {
    time_t cur_time = std::time(0);
    struct tm *now = std::localtime(&cur_time);

    char s[100];
    sprintf(s, "%02d-%02d-%02d_%02d-%02d-%02d", now->tm_year % 100, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

    return s;
}

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

    std::string date = get_date_string();
    params.write_to_file(date + "_params.txt");

    std::ofstream outf(date + "_coords.txt");
    std::ofstream outforces(date + "_forces.txt");

    model.read_positions("initial_coords_40.txt");
    model.forces.emplace_back(new spheres_interaction_force_unfold(params.N, 179, model.pair_forces));
    model.forces.emplace_back(new hydro(model.mass_center));
    model.forces.emplace_back(new random_force(179));

    // Main loop over time

    for (int s = 0; s < params.ns; s++) {
        model.iterate();
        if (s % params.nfac == 0) {
            cout << s << endl;
            cout << model.mass_center.x << " " << model.mass_center.y << " " << model.mass_center.z << endl;
            model.write_to_file(outf, s / params.nfac);
            model.write_pair_forces(outforces, s / params.nfac);
        }
    }

    outf.close();
    outforces.close();

    return 0;
}
