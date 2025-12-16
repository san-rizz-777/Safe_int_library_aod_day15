#include "./mult.h"
#include "Overflow.h"
#include <cstdint>
#include <initializer_list>
#include <string>

/* ============================================================
 * MUL DISPATCHERS — one per Overflow.h function
 * ============================================================ */

template<typename T, typename U>
struct MulDispatcher;

/* char */
template<> struct MulDispatcher<char, char> {
    static void run(char a, char b) {
        Overflow::safe_mul_char_char(a, b);
    }
};

/* unsigned char */
template<> struct MulDispatcher<unsigned char, unsigned char> {
    static void run(unsigned char a, unsigned char b) {
        Overflow::safe_mul_uchar_uchar(a, b);
    }
};

/* short */
template<> struct MulDispatcher<short, short> {
    static void run(short a, short b) {
        Overflow::safe_mul_short_short(a, b);
    }
};

/* unsigned short */
template<> struct MulDispatcher<unsigned short, unsigned short> {
    static void run(unsigned short a, unsigned short b) {
        Overflow::safe_mul_ushort_ushort(a, b);
    }
};

/* int */
template<> struct MulDispatcher<int, int> {
    static void run(int a, int b) {
        Overflow::safe_mul_int_int(a, b);
    }
};

/* unsigned int */
template<> struct MulDispatcher<unsigned int, unsigned int> {
    static void run(unsigned int a, unsigned int b) {
        Overflow::safe_mul_uint_uint(a, b);
    }
};

/* int32_t */
template<> struct MulDispatcher<int32_t, int32_t> {
    static void run(int32_t a, int32_t b) {
        Overflow::safe_mul_int32_int32(a, b);
    }
};

/* uint32_t */
template<> struct MulDispatcher<uint32_t, uint32_t> {
    static void run(uint32_t a, uint32_t b) {
        Overflow::safe_mul_uint32_uint32(a, b);
    }
};

/* int64_t */
template<> struct MulDispatcher<int64_t, int64_t> {
    static void run(int64_t a, int64_t b) {
        Overflow::safe_mul_int64_int64(a, b);
    }
};

/* uint64_t */
template<> struct MulDispatcher<uint64_t, uint64_t> {
    static void run(uint64_t a, uint64_t b) {
        Overflow::safe_mul_uint64_uint64(a, b);
    }
};

/* ============================================================
 * VERIFY BASE (repo-style)
 * ============================================================ */

template<typename T, typename U>
class MultVerifyBase {
public:
    MultVerifyBase(const std::string& name, Table<T, U>& t) {
        TestSuite<T, U, Operation::Multiply> tests;

        for (const auto& c : tests.get_cases()) {
            bool success = true;
            try {
                MulDispatcher<T, U>::run(c.first(), c.second());
            } catch (...) {
                success = false;
            }

            const std::string verdict =
                (success != c.is_success()) ? "FAILED" : "PASSED";
            const std::string expected =
                (c.is_success()) ? "True" : "False";

            t.addRow(name, c.first(), c.second(), expected, verdict);
        }
    }
};

/* ============================================================
 * RUNNER
 * ============================================================ */

void TestMult::run() {
    std::initializer_list<std::string> heading(
        {"Multiplication", "x", "y", "Expected", "Verdict"}
    );

    {
        Table<char, char> t(heading);
        MultVerifyBase<char, char>("char_char", t);
        t.print(std::cout);
    }

    {
        Table<unsigned char, unsigned char> t(heading);
        MultVerifyBase<unsigned char, unsigned char>("uchar_uchar", t);
        t.print(std::cout);
    }

    {
        Table<short, short> t(heading);
        MultVerifyBase<short, short>("short_short", t);
        t.print(std::cout);
    }

    {
        Table<unsigned short, unsigned short> t(heading);
        MultVerifyBase<unsigned short, unsigned short>("ushort_ushort", t);
        t.print(std::cout);
    }

    {
        Table<int, int> t(heading);
        MultVerifyBase<int, int>("int_int", t);
        t.print(std::cout);
    }

    {
        Table<unsigned int, unsigned int> t(heading);
        MultVerifyBase<unsigned int, unsigned int>("uint_uint", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, int32_t> t(heading);
        MultVerifyBase<int32_t, int32_t>("int32_int32", t);
        t.print(std::cout);
    }

    {
        Table<uint32_t, uint32_t> t(heading);
        MultVerifyBase<uint32_t, uint32_t>("uint32_uint32", t);
        t.print(std::cout);
    }

    {
        Table<int64_t, int64_t> t(heading);
        MultVerifyBase<int64_t, int64_t>("int64_int64", t);
        t.print(std::cout);
    }

    {
        Table<uint64_t, uint64_t> t(heading);
        MultVerifyBase<uint64_t, uint64_t>("uint64_uint64", t);
        t.print(std::cout);
    }

    // ✔ all Overflow.h multiplication combinations covered
}
