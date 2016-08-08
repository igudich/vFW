#include <vector>
#include "vect.h"

class force {
  public:
    virtual std::vector<vect> get_velocity_increment(const std::vector<vect>& position) {
        return std::vector<vect>();
    }
};
