#ifndef MODEL_H_
#define MODEL_H_

#include "vwf_model.h"
#include <vector>
#include <fstream>

class model {
  public:
    std::vector<vwf_model> proteins;
    parameters params;

    model(int n);

    void iterate();
    void write_to_file(std::ofstream & fout, int i);
};

#endif //MODEL_H_
