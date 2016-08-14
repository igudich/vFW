#include "model.h"

model::model(int n) {
    for (int i = 0; i < n; i++)
        proteins.push_back(vwf_model(params));
//    proteins.resize(n, vwf_model(params)); 
}

void model::iterate() {
    for (int i = 0; i < (int)proteins.size(); i++)
        proteins[i].calculate_velocities();
    for (int i = 0; i < (int)proteins.size(); i++)
        proteins[i].move_protein();
}

void model::write_to_file(std::ofstream & outf, int i) {
    outf << std::endl;
    outf << "* " << i << std::endl;
    int si = 1;
    for (int i = 0; i < proteins.size(); i++) {
        for (vect u : proteins[i].position) {
            outf << u.x << " " << u.y << " " << u.z << std::endl;
            si++;
        }
    }
}
