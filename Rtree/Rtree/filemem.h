#pragma once
#include "base.h"
#include "mem.h"

class Rentry;

class FileMemory:public Memory {
//data members
public:
	fstream m_memfile; //file path
	int m_freelist;
	int m_largest;
	char* m_buffer;
//public functions
public:
	//constructor
	FileMemory(const int a_page_size, const char* file_name, Rentry* (*a_fromMem)(const char* a_p, int &a_len, const int a_dimen, const bool a_is_point), const bool a_new = false);
	virtual ~FileMemory();

	Rentry* (*m_fromMem)(const char* a_p, int &a_len, const int a_dimen, const bool a_is_point);
	virtual Rnode load_page(const int a_pageid);
	virtual int allocate_page();
	virtual void write_page(const int a_pageid, const Rnode* a_p);
	virtual void remove_page(const int a_pageid);
	virtual void flush();

};