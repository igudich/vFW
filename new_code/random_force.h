#pragma once
#include "C:\Users\gosha\vFW_repo\new_code\force.h"
#include <random>

class random_force : public force
{
	std::default_random_engine generator; 
	std::normal_distribution<double> distribution;
public:
	random_force(unsigned seed);
	~random_force();
	std::vector<vect> get_velocity_increment(const parameters& params, const std::vector<vect>& position);
};

