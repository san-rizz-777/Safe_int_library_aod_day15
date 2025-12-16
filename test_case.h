#pragma once
#include <ostream>
enum Operation {
	Add,
	Multiply,
	Divide,
	Subtract,
	Cast
};


template<typename T, typename U, Operation op>
class TestCase {
private:	
	const T x;
	const U y;
	const bool success;
public:
	TestCase(T _x, U _y, bool _success) :
		x(_x),
		y(_y),
		success(_success){}
	const T first() const { return x;}
	const U second() const { return y;}
	const bool is_success() const { return success; }
};

template<typename T, typename U, Operation op>
std::ostream & operator<<(std::ostream & os, const TestCase<T, U, op> & c) {
	os << c.first() << " | " << c.second() << " | " << (c.is_success() ? "true" : "false");
	return os;
}
