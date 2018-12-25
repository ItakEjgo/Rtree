#include "filemem.h"

struct Header {
	int m_root_page;
	int m_freelist;
	int m_largest;
};

FileMemory::FileMemory(const int a_page_size, const char* file_name, Rentry* (*a_fromMem)(const char* a_p, int &a_len, const int a_dimen, const bool a_is_point), const bool a_new = false):Memory(a_page_size), m_fromMem(a_fromMem), m_freelist(-1), m_largest(0) {
	if (a_new) {
		m_memfile.open(file_name, fstream::in | fstream::out | fstream::binary | fstream::trunc);
		flush();
	}
	else {
		m_memfile.open(file_name, fstream::in | fstream::out | fstream::binary);
		m_memfile.seekg(0);
		Header hdr;
		m_memfile.read((char*)&hdr, sizeof(hdr));
		m_root_page_id = hdr.m_root_page;
		m_freelist = hdr.m_freelist;
		m_largest = hdr.m_largest;
	}
	m_buffer = new char[a_page_size];
}

FileMemory::~FileMemory(){
	m_memfile.seekg(0);
	Header hdr;
	hdr.m_root_page = m_root_page_id;
	hdr.m_freelist = m_freelist;
	hdr.m_largest = m_largest;
	m_memfile.write((char*)&hdr, sizeof(hdr));
	m_memfile.close();
	delete m_buffer;
}

Rnode FileMemory::load_page(const int a_page_id) {
	int len = 0;
	m_memfile.seekg(a_page_id * m_page_size + sizeof(Header));
	m_memfile.read(m_buffer, m_page_size);
	Rnode n = Rnode::fromMem()
}