#include "rentry.h"

Rentry::Rentry() {}

Rentry::Rentry(const Rentry &a_rentry) {
	m_pageid = a_rentry.m_pageid;
	m_hc = a_rentry.m_hc;
	m_num_of_records = a_rentry.m_num_of_records;
}

Rentry::Rentry(int a_pageid, Hypercube a_hc, unsigned int a_num_of_records) :
	m_pageid(a_pageid), m_hc(a_hc), m_num_of_records(a_num_of_records) {}

Rentry::~Rentry(){}

bool Rentry::operator==(const Rentry &a_entry) {
	for (unsigned int i = 0; i < DIMENSION; i++) {
		if (a_entry.m_hc.m_lower.m_value[i] != m_hc.m_lower.m_value[i]) return false;
		if (a_entry.m_hc.m_upper.m_value[i] != m_hc.m_upper.m_value[i]) return false;
	}
	return true;
}