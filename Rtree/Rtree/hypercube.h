#pragma once
#include "base.h"
#include "point.h"

class Hypercube {
//data members
public:
	Point m_lower;	//lower corner of the hypercube
	Point m_upper;	//upper corner of the hypercube

//public functions
public:
	//constructor
	Hypercube();
	Hypercube(const Point &a_lower, const Point &a_upper);
	Hypercube(const Hypercube &a_hc);
	virtual ~Hypercube();

	//minimum distance to a hypercube
	db min_distance_to(const Hypercube &a_hc);

	//maximum distance to a hypercube
	db max_distance_to(const Hypercube &a_hc);

	//the center of the hypercube
	Point center();

	//the diagonal distance
	db diag_distance();

	//check whether this hypercube contain a hypercube
	bool is_contain(const Hypercube &a_hc);

	//check whether this hypercube intersect with a hypercube
	bool is_intersect(const Hypercube &a_hc);

	//return the intersection of two hypercubes
	/*
	******Please call after check is_intersect() ******
	*/
	Hypercube intersect(const Hypercube &a_hc);

	//combine two hypercubes
	Hypercube combine(const Hypercube &a_hc);

	//extend the hypercube in each dimension
	void extend(vector<db> a_sidelen);
};