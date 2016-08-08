#ifndef SPHERES_INTERACTION_H_
#define SPHERES_INTERACTION_H_

#include "force.h"
#include "params.h"

class spheres_interaction_force : public force {
  public:
    spheres_interaction_force();
    std::vector<vect> get_velocity_increment(const parameters& params, const std::vector<vect>& position);
};

#endif // SPHERES_INTERACTION_H_
