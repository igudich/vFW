#ifndef VWF_MODEL_H_
#define VWF_MODEL_H_

#include <vector>
#include "vect.h"
#include "force.h"

class vwf_model {
    std::vector<vect> position;
    std::vector<vect> velocities;
    parameters &params;
    void recalc_mass_center();
  public:
    vect mass_center;
    std::vector<force> forces;

    vwf_model(parameters &_params);
    void read_positions(std::string filename);

    void iterate();
};

#endif // VWF_MODEL_H_
