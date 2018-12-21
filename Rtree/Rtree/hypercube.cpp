#include "hypercube.h"

Hypercube::Hypercube() {}

Hypercube::Hypercube(const Point &a_lower, const Point &a_upper) {
	m_lower = a_lower;
	m_upper = a_upper;
}

Hypercube::Hypercube(const Hypercube &a_hc) {
	m_lower = a_hc.m_lower;
	m_upper = a_hc.m_upper;
}

Hypercube::~Hypercube() {}

db Hypercube::min_distance_to(const Hypercube &a_hc) {
	db ret = 0.0;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		db dis = 0.0;
		if (dcmp(m_lower.m_value[i] - a_hc.m_upper.m_value[i]) > 0) {
			dis = m_lower.m_value[i] - a_hc.m_upper.m_value[i];
		}
		else if (dcmp(a_hc.m_lower.m_value[i] - m_upper.m_value[i]) < 0) {
			dis = a_hc.m_lower.m_value[i] - m_upper.m_value[i];
		}
		ret += sqr(dis);
	}
	return sqrt(ret);
}

db Hypercube::max_distance_to(const Hypercube &a_hc) {
	db ret = 0.0;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		db low_to_up = sqr(m_lower.m_value[i] - a_hc.m_upper.m_value[i]);
		db up_to_low = sqr(m_upper.m_value[i] - a_hc.m_lower.m_value[i]);
		ret += low_to_up > up_to_low ? low_to_up : up_to_low;
	}
	return sqrt(ret);
}

Point Hypercube::center() {
	Point ret;
	ret.m_value.clear();
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret.m_value.push_back((m_lower.m_value[i] + m_upper.m_value[i]) * 0.5);
	}
	return ret;
}

db Hypercube::diag_distance() {
	return m_lower.distance_to(m_upper);
}


bool Hypercube::is_contain(const Hypercube &a_hc) {
	for (unsigned int i = 0; i < DIMENSION; i++) {
		if (dcmp(m_lower.m_value[i] - a_hc.m_lower.m_value[i]) > 0) return false;
		if (dcmp(m_upper.m_value[i] - a_hc.m_upper.m_value[i]) < 0) return false;
	}
	return true;
}

bool Hypercube::is_intersect(const Hypercube &a_hc) {
	if (is_contain(a_hc)) return false;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		if (dcmp(m_lower.m_value[i] - a_hc.m_upper.m_value[i]) > 0) return false;
		if (dcmp(m_upper.m_value[i] - a_hc.m_lower.m_value[i]) < 0) return false;
	}
	return true;
}

Hypercube Hypercube::intersect(const Hypercube &a_hc) {
	//need to check whether they are intersect
	Hypercube ret;
	ret.m_lower.m_value.clear();
	ret.m_upper.m_value.clear();
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret.m_lower.m_value.push_back(max(m_lower.m_value[i], a_hc.m_lower.m_value[i]));
		ret.m_upper.m_value.push_back(min(m_upper.m_value[i], a_hc.m_upper.m_value[i]));
	}
	return ret;
}

Hypercube Hypercube::combine(const Hypercube &a_hc) {
	Hypercube ret;
	ret.m_lower.m_value.clear();
	ret.m_upper.m_value.clear();
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret.m_lower.m_value.push_back(min(m_lower.m_value[i], a_hc.m_lower.m_value[i]));
		ret.m_upper.m_value.push_back(max(m_upper.m_value[i], a_hc.m_upper.m_value[i]));
	}
	return ret;
}

void Hypercube::extend(vector<db> a_sidelen) {
	for (unsigned int i = 0; i < DIMENSION; i++) {
		m_lower.m_value[i] -= a_sidelen[i];
		m_upper.m_value[i] += a_sidelen[i];
	}
}

db Hypercube::volume() {
	db ret = 1.0;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret *= (m_upper.m_value[i] - m_lower.m_value[i]);
	}
	return ret;
}

db Hypercube::perimeter() {
	db ret = 0;
	for (unsigned int i = 0; i < DIMENSION; i++) {
		ret += (m_upper.m_value[i] - m_lower.m_value[i]);
	}
	ret *= pow(2.0, DIMENSION - 1);
	return ret;
}
