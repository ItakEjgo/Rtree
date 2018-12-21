#pragma once
#include "base.h"

class Point {
//data member
public:
	vector<db> m_value;

//public functions
public:
	//constructor
	Point();
	Point(vector<db> &a_value);

	//destructor
	virtual ~Point();

	//check whether this point is valid
	bool valid();

	//distance from this point to a point p
	db distance_to(const Point &a_p);

};
