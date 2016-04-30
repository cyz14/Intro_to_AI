/*
	Last Changed on 2016-04-26
*/
#include "../lib/Answer.h"
#include <ctime>
#include <cassert>
#include <iostream>
#include <algorithm>


Answer::Answer(int size)
{
	if (size == 0) {
		std::cerr << "Size is 0." << std::endl;
	}
	for (int i = 0; i < size; ++i)
	{
		m_v.push_back(i);
	}
}

Answer::Answer(const Answer & ans) {
	for (int i = 0; i < ans.size(); ++i)
	{
		m_v.push_back(ans[i]);
	}
}

Answer::~Answer()
{
	// m_v.clear();
}

void Answer::random() {
	for (int i = 0; i < size(); ++i)
	{
		m_v[i] = i;
	}
	for (int i = size(); i > 0; --i)
	{
		int p = rand() % i;
		std::swap( m_v[i-1], m_v[p] );
	}
}

void Answer::random( int start, int end ) {
	if (start < end) {
		int number = end - start;
		for (size_t i = end; i > start; i--) {
			int tgt = rand() % number + start;
			std::swap( m_v[i-1], m_v[tgt]);
			number--;
		}
	} else if (end < start) {
		std::swap(m_v[start], m_v[end]);
		return;
		// int num = size();
		// for (size_t i = (end - 1 + num) % num, j = start; i != j; ) {
		// 	std::swap( m_v[i], m_v[j]);
		// 	if (i == (j + 1) % num)
		// 		 break;

		// 	i--;
		// 	i = (i + num) % num;
		// 	j++;
		// 	j %= num;
	}
}

double Answer::rand_0_1() {
	return double(rand()) / RAND_MAX;
}

void Answer::randomUV(int & u, int & v, int last_u, int last_v) {
	int nc = size();
	while (u == v || (u == last_u && v == last_v)) {
		int offset = rand() % nc;
		if (rand_0_1() > 0.5)
		{
			offset = 0;
		}
		u = ((long long)rand() + offset) % nc;
		v = ((long long)rand() + offset) % nc;
	}
}

void Answer::print(std::ostream & fout) {
	int N = size();
	for (int i = 0; i < N; ++i)
	{
		fout << m_v[i];
		if (i == N - 1)
			fout << std::endl;
		else
			fout << ' ';
	}
}

void Answer::setAt(int pos, int num) {
	assert(pos < size());
	m_v[pos] = num;
}

int Answer::operator [] (int pos) const
{
	assert(pos < size() && pos >= 0);
	return m_v[pos];
}

Answer & Answer::operator = (const Answer & right) {
	int _size = right.size();
	for (int i = 0; i < _size; ++i)
	{
		m_v[i] = right[i];
	}
	return *this;
}
