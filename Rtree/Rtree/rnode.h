#pragma once
#include "hypercube.h"
#include "rentry.h"

//node status
const int NODE_UNCHANGED = 6666;
const int NODE_CHANGED = 6667;
const int NODE_OVERFLOW = 6668;
const int NODE_UNDERFULL = 6669;

//to be writen in Rtree.cpp
const int m_minLeaf = 2;
const int m_maxLeaf = 4;
const int m_minNode = 2;
const int m_maxNode = 4;

class Rtree;

class Rnode {
//data members
public:
	const Rtree* m_rtree; //which Rtree this node belongs to
	int m_pageid; //the pageid of this rnode
	unsigned int m_level; //the level of this rnode (leaf: 0)
	int m_parent; //the pageid of the parent, -1 if not exists
	vector<Rentry> m_entries;//the list of rentries
//public functions
public:
	//constructors
	Rnode();
	Rnode(const Rnode &a_rn);
	Rnode(Rtree* a_rtree, int a_pageid, unsigned int a_level, int a_parent);
	virtual ~Rnode();

	//check whether this node is root
	bool is_root();

	//check whether this node is leaf
	bool is_leaf();

	//generate the new entry of this node
	Rentry generate_entry();

	//***** Important ****
	int insert(const Rentry &a_entry);
	int remove(const Rentry &a_entry);
	int replace(const Rentry &a_entry);
};