#include "rnode.h"

Rnode::Rnode(){}

Rnode::Rnode(const Rnode &a_rn) {
	m_rtree = a_rn.m_rtree;
	m_pageid = a_rn.m_pageid;
	m_level = a_rn.m_level;
	m_parent = a_rn.m_parent;
	m_entries = a_rn.m_entries;
}

Rnode::Rnode(Rtree* a_rtree, int a_pageid, unsigned int a_level, int a_parent) :
	m_rtree(a_rtree), m_pageid(a_pageid), m_level(a_level), m_parent(a_parent) {}

Rnode::~Rnode() {}

bool Rnode::is_root() {
	return m_parent == -1;
}

bool Rnode::is_leaf() {
	return !m_level;
}

Rentry Rnode::generate_entry() {
	Rentry new_entry = Rentry(m_pageid, m_entries[0].m_hc, m_entries[0].m_num_of_records);
	for (unsigned int i = 1; i < m_entries.size(); i++) {
		new_entry.m_hc = new_entry.m_hc.combine(m_entries[i].m_hc);
		new_entry.m_num_of_records += m_entries[i].m_num_of_records;
	}
	return new_entry;
}

int Rnode::insert_status_check(const Rentry &a_entry) {
	int status = NODE_UNCHANGED;
	Rentry old_entry = generate_entry();
	m_entries.push_back(a_entry);
	Rentry new_entry = generate_entry();
	int limit = is_leaf() ? m_maxLeaf : m_maxNode;
	if (m_entries.size() > limit) {
		status = NODE_OVERFLOW;
	}
	else {
		status = (old_entry == new_entry) ? NODE_UNCHANGED : NODE_CHANGED;
	}
	return status;
}
