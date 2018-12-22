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

int Rnode::insert(const Rentry &a_entry) {
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

int Rnode::remove(const Rentry &a_entry) {
	int status = NODE_UNCHANGED;
	int id = -1;
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		if (m_entries[i].m_pageid == a_entry.m_pageid) {
			id = i;
			break;
		}
	}
	if (id == -1) return status;
	Rentry old_entry = generate_entry();
	swap(m_entries[id], m_entries[m_entries.size() - 1]);
	m_entries.pop_back();
	Rentry new_entry = generate_entry();
	if (id >= 0) {
		int limit = is_leaf() ? m_minLeaf : m_minNode;
		if (m_entries.size() < limit) {
			status = NODE_UNDERFULL;
		}
		else {
			status = old_entry == new_entry ? NODE_UNCHANGED : NODE_CHANGED;
		}
	}
	return status;
}

int Rnode::replace(const Rentry &a_entry) {
	int status = NODE_UNCHANGED;
	for (unsigned int i = 0; i < m_entries.size(); i++) {
		if (m_entries[i].m_pageid == a_entry.m_pageid) {
			if (!(m_entries[i] == a_entry)) {
				status = NODE_CHANGED;
				m_entries[i] = a_entry;
			}
			break;
		}
	}
	return status;
}
