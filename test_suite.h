#pragma once
#include "./test_case.h"
#include <vector>

template<typename T, typename U, Operation op>
class TestSuite {
typedef std::vector<TestCase<T, U, op>> TestVector;
private:
	const TestVector & cases;
public:
	TestSuite();
	const TestVector & get_cases() {
		return cases;
	}
};
