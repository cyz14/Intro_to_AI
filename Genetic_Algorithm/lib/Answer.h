#ifndef ANSWER_H
#define ANSWER_H

#include <iostream>
#include <fstream>
#include <vector>
class Answer {
private:
	std::vector<int> m_v;
public:
	Answer( int size = 0 );
	Answer( const Answer & );
	~Answer();
	int  size() const { return m_v.size(); }
	void random();
	static double rand_0_1();
	void random( int start, int end );
	void randomUV( int & u, int & v, int last_u, int last_v );
	void print( std::ostream & fout = std::cout);
	void setAt( int pos, int num );
	void reverse();
	int operator [] ( int pos ) const;
	Answer & operator = ( const Answer & right );
};

#endif
