#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRangeList;

class CRange
{
      public:
	CRange(long long lo, long long hi);

	void print();

	CRangeList operator+(const CRange & range);
	CRangeList operator-(const CRange & range);

	long long m_lo;
	long long m_hi;
      private:
};

class CRangeList
{
      public:
	CRangeList();

	CRangeList operator+=(CRange range);

	CRangeList operator+=( const CRangeList & list);
	CRangeList operator-=( CRange range);
	CRangeList operator-=( const CRangeList & list);
	CRangeList & operator=( CRange range);
	CRangeList & operator=( const CRangeList & list);
	bool operator==(const CRangeList & list) const;
	bool operator!=(const CRangeList & list) const;
	CRangeList & operator+(const CRange & range);
	CRangeList & operator-(const CRange & range);
	bool includes(long long value) const;
	bool includes(const CRange & range) const;


	void print();

	vector<CRange> vec;
      private:
	void simplify();
};

CRange::CRange(long long lo, long long hi) {
	if (hi < lo)
		throw logic_error("hi <= lo");
	m_lo = lo;
	m_hi = hi;
}

void CRange::print() {
	if (m_lo != m_hi)
		cout << "<" << m_lo << ", " << m_hi << ">" << endl;
	else
		cout << m_lo << endl;
}

CRangeList CRange::operator+(const CRange & range) {

	CRangeList list;
	list = *this;
	list += range;
	return list;
}




CRangeList CRange::operator-(const CRange &range) {

	CRangeList list;
	list = *this;
	list -= range;
	return list;

}

CRangeList::CRangeList() {
	vec = {};
}

void CRangeList::print() {
	for (CRange elem : vec) {
		elem.print();
	}
}

CRangeList CRangeList::operator+=(const CRange range) {
	unsigned int size = vec.size();
	unsigned int i;
	for (i = 0; i < size; i++) {
		if (vec[i].m_lo > range.m_lo ) {
			vec.insert(vec.begin() + i, range);
			break;
		}
		if (vec[i].m_lo == range.m_lo) {
			if (range.m_hi > vec[i].m_hi) {
				vec.insert(vec.begin() + i, range);
				break;
			}
			else {							//useless case
				vec.insert(vec.begin() + i + 1, range);
				break;

			}

		}
	}
	if (i == size)
		vec.insert(vec.end(), range);
	simplify();
	return *this;
}

void CRangeList::simplify() {
	unsigned int i;
	if (vec.size() == 1)
		return;
	for (i = 0; i < vec.size(); i++) {
		if (vec.begin() + i + 1 == vec.end())
			return;
		if (vec[i].m_hi + 1 >= vec[i + 1].m_lo) {
			if (vec[i].m_hi <= vec[i + 1].m_hi) {
				vec[i].m_hi = vec[i+1].m_hi;
			}
			vec.erase(vec.begin() + i + 1);
			i--;
		}
	}
}

CRangeList CRangeList::operator+=(const CRangeList & list) {
	for (CRange elem : list.vec) {
		*this += elem;
	}
	return *this;
}

CRangeList CRangeList::operator-=(const CRange range) {

	unsigned int i;
	for (i = 0; i < vec.size(); i++) {
		if (vec[i].m_lo >= range.m_lo && vec[i].m_hi > range.m_hi && vec[i].m_lo <= range.m_hi) {
			vec[i].m_lo = range.m_hi + 1;
		}

		if (vec[i].m_lo < range.m_lo && vec[i].m_hi <= range.m_hi && vec[i].m_hi >= range.m_lo) {
			vec[i].m_hi = range.m_lo - 1;
		}


		if (vec[i].m_lo < range.m_lo && vec[i].m_hi > range.m_hi) {
			vec.insert(vec.begin() + i + 1, CRange(range.m_hi + 1, vec[i].m_hi));
			vec[i].m_hi = range.m_lo - 1;
		}
		if (vec[i].m_lo >= range.m_lo && vec[i].m_hi <= range.m_hi) {
			vec.erase(vec.begin() + i);
			i--;
		}
	}

	return *this;
}

CRangeList CRangeList::operator-=(const CRangeList & list) {

	for (CRange elem : list.vec) {
		*this -= elem;
	}
	return *this;
}


CRangeList & CRangeList::operator=(const CRange range) {
	vec = {range};
	vec.shrink_to_fit();
	return *this;
}


CRangeList &CRangeList::operator=(const CRangeList & list) {
	vec = list.vec;
	return *this;

}

bool CRangeList::operator==(const CRangeList &list) const{
	unsigned int size = vec.size();
	if (size != list.vec.size())
		return false;
	for (unsigned int i = 0; i < size; i++) {
		if (vec[i].m_lo != list.vec[i].m_lo || vec[i].m_hi != list.vec[i].m_hi)
			return false;
	}

	return true;

}

bool CRangeList::operator!=(const CRangeList &list) const {
	return !(*this == list);
}

CRangeList &CRangeList::operator+(const CRange &range) {

	*this += range;
	return *this;

}

CRangeList &CRangeList::operator-(const CRange &range) {
	*this -= range;
	return *this;
}

bool CRangeList::includes(long long int value) const {

	for (CRange elem : this->vec) {
		if (elem.m_lo <= value && elem.m_hi >= value)
			return true;
	}
	return false;
}

bool CRangeList::includes(const CRange &range) const {

	unsigned int size = vec.size();

	for (unsigned int i = 0; i < size; i++) {

		if (vec[i].m_lo <= range.m_lo && vec[i].m_hi >= range.m_hi)
			return true;

	}
	return false;

}

ostream & operator<<(ostream & os, const CRangeList & list ) {
	unsigned int i, size = list.vec.size();
	os << "{";
	for (i = 0; i < size; i++) {

		if (i != size - 1) {
			if (list.vec[i].m_lo != list.vec[i].m_hi)
				os << "<" << list.vec[i].m_lo << ".." << list.vec[i].m_hi << ">,";
			else
				os << list.vec[i].m_lo << ",";
		}
		else {
			if (list.vec[i].m_lo != list.vec[i].m_hi)
				os << "<" << list.vec[i].m_lo << ".." << list.vec[i].m_hi << ">";
			else
				os << list.vec[i].m_lo;
		}
	}
	os << "}";
	return os;
}

#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
  CRangeList a, b;


  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );


	a = CRange (5, 10);
	a += CRange ( 25, 100 );
	assert ( toString ( a ) == "{<5..10>,<25..100>}" );
	a += CRange ( -5, 0 );
	a += CRange ( 8, 50 );
	assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
	a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
	assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
	a += CRange ( 106, 119 ) + CRange ( 152, 158 );
	assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
	a += CRange ( -3, 170 );
	a += CRange ( -30, 1000 );
	assert ( toString ( a ) == "{<-30..1000>}" );
	b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
	a += b;
	assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
	a -= CRange ( -400, -400 );
	assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
	a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
	assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
	try
	{
	  a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
	  assert ( "Exception not thrown" == nullptr );
	}
	catch ( const std::logic_error & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown" == nullptr );
	}
	assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
	b = a;
	assert ( a == b );
	assert ( !( a != b ) );
	b += CRange ( 2600, 2700 );
	assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
	assert ( a == b );
	assert ( !( a != b ) );
	b += CRange ( 15, 15 );
	assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
	assert ( !( a == b ) );
	assert ( a != b );
	assert ( b . includes ( 15 ) );
	assert ( b . includes ( 2900 ) );
	assert ( b . includes ( CRange ( 15, 15 ) ) );
	assert ( b . includes ( CRange ( -350, -350 ) ) );
	assert ( b . includes ( CRange ( 100, 200 ) ) );
	assert ( !b . includes ( CRange ( 800, 900 ) ) );
	assert ( !b . includes ( CRange ( -1000, -450 ) ) );
	assert ( !b . includes ( CRange ( 0, 500 ) ) );
	a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
	assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
	b += a;
	assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
	b -= a;
	assert ( toString ( b ) == "{}" );
	b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
	assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
	b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
	assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
	#ifdef EXTENDED_SYNTAX
	CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
	assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
	ostringstream oss;
	oss << setfill ( '=' ) << hex << left;
	for ( const auto & v : x + CRange ( -100, -100 ) )
	  oss << v << endl;
	oss << setw ( 10 ) << 1024;
	assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
      #endif /* EXTENDED_SYNTAX */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
