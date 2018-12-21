#include "point.h"

Point::Point() {}

Point::Point(vector<db> &a_value) {
	m_value.clear();
	for (unsigned int i = 0; i < a_value.size(); i++) {
		m_value.push_back(a_value[i]);
	}
}

Point::~Point() {}

bool Point::valid() {
	return m_value.size() == DIMENSION;
}

db Point::distance_to(const Point &a_p) {
	db ret = 0.0;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret += sqr(m_value[i] - a_p.m_value[i]);
	}
	return sqrt(ret);
}


