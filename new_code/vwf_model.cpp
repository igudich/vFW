#include "vwf_model.h"
#include <fstream>

vwf_model::vwf_model(parameters& _params) {
    params = params;
}

void vwf_model::read_positions(std::string filename) {
    std::ifstream fin(filename);
    position.resize(params.N);
    velocities.resize(params.N);
    for (int i = 0; i < params.N; i++) {
        fin >> position[i].x >> position[i].y >> position[i].z;
    }
    fin.close();
    recalc_mass_center();
}

void vwf_model::recalc_mass_center() {
    mass_center = vect();
    for (int i = 0; i < params.N; i++)
        mass_center = mass_center + params[i];
    mass_center = (1 / params.N) * mass_center;
}

void vwf_model::iterate() {
    for (force f : forces) {
        std::vector<vect> deltas = f.get_velocity_increment(params, position);
        for (int i = 0; i < params.N; i++) {
            velocities[i] += deltas[i];
        }
    }
    for (int i = 0; i < params.N; i++) {
        position[i] += velocities[i] * params.dt;
    }
    recalc_mass_center();
}
