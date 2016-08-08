#include "force.h"

class spheres_interaction_force : public force {
  public:
    spheres_interaction_force();
    std::vector<vect> get_velocity_increment(const std::vector<vect>& position);
};
