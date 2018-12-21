#pragma once
#include "base.h"
#include "hypercube.h"

class Rentry {
//data members
public:
	int m_pageid;   //pageid of this entry
	Hypercube m_hc;	//the hypercube that cover this entry
	unsigned int m_num_of_records;//the number of records
//public functions
public:
	//constructors
	Rentry();
	Rentry(const Rentry &a_rentry);
	Rentry(int a_pageid, Hypercube a_hc, unsigned int m_cnt);
	virtual ~Rentry();

	bool operator == (const Rentry &a_entry);
};