#include <vector>

struct vect {
    double x, y, z;
};

class force {
  public:
    virtual std::vector<vect> get_force(const std::vector<vect>& position) {
        return std::vector<vect>();
    }
};
