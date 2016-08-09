#include <vector>
#include "vect.h"
#include "force.h"

using namespace std;

class hydro: public force {
  public:
    vector<vect> get_velocity_increment(const parameters& params, const std::vector<vect>& position);
    double srat;
    double erat;
    vect mass_center;
};
