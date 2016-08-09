#include "random_force.h"


random_force::random_force(unsigned seed) : generator(seed), distribution(0.0, 1.0)
{
}


random_force::~random_force()
{
}

std::vector<vect> random_force::get_velocity_increment(const parameters& params, const std::vector<vect>& position)
{
	std::vector<vect> res;

	vect v(0, 0, 0);
	for (int i = 0; i < position.size(); ++i)
	{
		v.x += distribution(generator)*params.mno;
		v.y += distribution(generator)*params.mno;
		v.z += distribution(generator)*params.mno;
		res.push_back((1 / params.gamma)*v);
	}
	return res;
}
