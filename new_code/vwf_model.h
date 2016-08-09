#ifndef VWF_MODEL_H_
#define VWF_MODEL_H_

#include <vector>
#include <memory>
#include "vect.h"
#include "force.h"

class vwf_model {
    std::vector<vect> position;
    void recalc_mass_center();
  public:
    parameters params;
    vect mass_center;
    std::vector<std::unique_ptr<force> > forces;

    vwf_model();
    void read_positions(std::string filename);
    void write_to_file(std::ofstream & fout, int it);

    void iterate();
};

#endif // VWF_MODEL_H_
