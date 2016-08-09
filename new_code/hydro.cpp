#include "hydro.h"
std::vector<vect> hydro::get_velocity_increment(const parameters& params, const std::vector<vect>& position){	
	
	std::vector <vect> dv (position.size());
	for (int i=0; i<(int)position.size(); i++){
		double dx = position[i].x-mass_center.x;
		double dy = position[i].y-mass_center.y;
		double dz = position[i].z-mass_center.z;
		
		dv[i].x = dx*erat + dz*srat;
		dv[i].y = dy*erat*(-1);
		dv[i].z = 0;

	}
	return dv;
}
