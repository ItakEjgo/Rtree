#pragma once
class Rtree;
class Rnode;

class Memory {
//data members
public:
	Rtree * m_rtree;
	int m_root_page_id;
	const int m_page_size;

public:
	Memory(const int a_page_size) :m_root_page_id(-1), m_page_size(a_page_size) {}
	virtual ~Memory() {}
	virtual Rnode load_page(const int a_pageid) = 0;
	virtual int allocate_page() = 0;
	virtual void write_page(const int a_pageid, const Rnode* m_p) = 0;
	virtual void remove_page(const int a_pageid) = 0;
	virtual void flush() = 0;
};