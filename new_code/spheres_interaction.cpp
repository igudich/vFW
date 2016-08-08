#include "spheres_interaction.h"
#include "params.h"
#include <cassert>
#include <cmath>

spheres_interaction_force::spheres_interaction_force() {}

std::vector<vect> spheres_interaction_force::get_velocity_increment(const parameters& params, const std::vector<vect>& position) {
    std::vector<vect> forces(params.N);

    for (int i = 0; i < params.N; i++) {
        for (int j = i + 1; j < params.N; j++) {
            vect dv(position[i], position[j]);
            double l = dv.length();

            assert(l > 1e-9); // NEVER compare doubles on equality!
            if (j == i + 1 || l < params.d) {
                vect fpr = (params.kspr * (l - params.d) / l) * dv;
                forces[i] = forces[i] + (-1) * fpr;
                forces[j] = forces[j] + fpr;
            } else if (params.d < l && l < 2 * params.d) {
                double u = std::exp(-((l - params.d) / params.d) * params.alpha);
                double u2 = 2 * params.alpha * params.kvdw * (u * (1 - u) / (l * params.d));

                vect fpr = u2 * dv;

                forces[i] = forces[i] + (-1) * fpr;
                forces[j] = forces[j] + fpr;
            }
        }
    }

    std::vector<vect> ret(params.N);
    for (int i = 0; i < params.N; i++) {
        ret[i] = params.dt * forces[i];
    }

    return ret;
}
