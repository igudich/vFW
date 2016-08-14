#include "params.h"
#include "vwf_model.h"
#include "model.h"
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

int main(int argc, char** argv) {
    model main_model(2);
    std::string parameters_filename;
    if (argc == 1)
        parameters_filename = "params.txt";
    else
        parameters_filename = argv[1];

    parameters & params = main_model.params;

    params.read_from_file(parameters_filename);

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

    cout << "x_file: " << params.x_file << endl;
    cout << "v_file: " << params.v_file << endl;
    cout << "srate_file: " << params.srate_file << endl << endl;

    std::string date = get_date_string();
    params.write_to_file(date + "_params.txt");

    std::ofstream outf(date + "_coords.txt");
    std::ofstream outforces(date + "_forces.txt");

    main_model.proteins[0].read_positions("initial_coords_40.txt");
    main_model.proteins[1].read_positions("initial_coords_40_2.txt");
    for (int i = 0; i < 2; i++) {
        main_model.proteins[i].forces.emplace_back(new spheres_interaction_force_unfold(params.N, time(0) + i, main_model.proteins[i].pair_forces));
        main_model.proteins[i].forces.emplace_back(new hydro_vessel(main_model.proteins[i].mass_center, params.x_file, params.srate_file, params.v_file));
        main_model.proteins[i].forces.emplace_back(new random_force(time(0) + i));
        for (int j = 0; j < 2; j++) {
            if (i != j)
                main_model.proteins[i].forces.emplace_back(new interprotein_interaction_force(main_model.proteins[j]));
        }

    }

    // Main loop over time

    for (int s = 0; s < params.ns; s++) {
        main_model.iterate();
        if (s % params.nfac == 0) {
            cout << s << endl;
//            cout << model.mass_center.x << " " << model.mass_center.y << " " << model.mass_center.z << endl;
            main_model.write_to_file(outf, s / params.nfac);
//            main_model.write_pair_forces(outforces, s / params.nfac);
        }
    }

    outf.close();
    outforces.close();

    return 0;
}
