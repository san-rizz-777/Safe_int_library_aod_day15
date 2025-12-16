#include "./div.h"
#include "Overflow.h"
#include <cstdint>
#include <initializer_list>
#include <string>

/* ============================================================
 * DIV DISPATCHERS — one per Overflow.h function
 * ============================================================ */

template<typename T, typename U>
struct DivDispatcher;

/* char */
template<> struct DivDispatcher<char, char> {
    static void run(char a, char b) {
        Overflow::safe_div_char_char(a, b);
    }
};

/* unsigned char */
template<> struct DivDispatcher<unsigned char, unsigned char> {
    static void run(unsigned char a, unsigned char b) {
        Overflow::safe_div_uchar_uchar(a, b);
    }
};

/* short */
template<> struct DivDispatcher<short, short> {
    static void run(short a, short b) {
        Overflow::safe_div_short_short(a, b);
    }
};

/* unsigned short */
template<> struct DivDispatcher<unsigned short, unsigned short> {
    static void run(unsigned short a, unsigned short b) {
        Overflow::safe_div_ushort_ushort(a, b);
    }
};

/* int */
template<> struct DivDispatcher<int, int> {
    static void run(int a, int b) {
        Overflow::safe_div_int_int(a, b);
    }
};

/* unsigned int */
template<> struct DivDispatcher<unsigned int, unsigned int> {
    static void run(unsigned int a, unsigned int b) {
        Overflow::safe_div_uint_uint(a, b);
    }
};

/* int32_t */
template<> struct DivDispatcher<int32_t, int32_t> {
    static void run(int32_t a, int32_t b) {
        Overflow::safe_div_int32_int32(a, b);
    }
};

/* uint32_t */
template<> struct DivDispatcher<uint32_t, uint32_t> {
    static void run(uint32_t a, uint32_t b) {
        Overflow::safe_div_uint32_uint32(a, b);
    }
};

/* int64_t */
template<> struct DivDispatcher<int64_t, int64_t> {
    static void run(int64_t a, int64_t b) {
        Overflow::safe_div_int64_int64(a, b);
    }
};

/* uint64_t */
template<> struct DivDispatcher<uint64_t, uint64_t> {
    static void run(uint64_t a, uint64_t b) {
        Overflow::safe_div_uint64_uint64(a, b);
    }
};

/* ============================================================
 * VERIFY BASE (repo-style)
 * ============================================================ */

template<typename T, typename U>
class DivVerifyBase {
public:
    DivVerifyBase(const std::string& name, Table<T, U>& t) {
        TestSuite<T, U, Operation::Divide> tests;

        for (const auto& c : tests.get_cases()) {
            bool success = true;
            try {
                DivDispatcher<T, U>::run(c.first(), c.second());
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

void TestDiv::run() {
    std::initializer_list<std::string> heading(
        {"Division", "x", "y", "Expected", "Verdict"}
    );

    {
        Table<char, char> t(heading);
        DivVerifyBase<char, char>("char_char", t);
        t.print(std::cout);
    }

    {
        Table<unsigned char, unsigned char> t(heading);
        DivVerifyBase<unsigned char, unsigned char>("uchar_uchar", t);
        t.print(std::cout);
    }

    {
        Table<short, short> t(heading);
        DivVerifyBase<short, short>("short_short", t);
        t.print(std::cout);
    }

    {
        Table<unsigned short, unsigned short> t(heading);
        DivVerifyBase<unsigned short, unsigned short>("ushort_ushort", t);
        t.print(std::cout);
    }

    {
        Table<int, int> t(heading);
        DivVerifyBase<int, int>("int_int", t);
        t.print(std::cout);
    }

    {
        Table<unsigned int, unsigned int> t(heading);
        DivVerifyBase<unsigned int, unsigned int>("uint_uint", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, int32_t> t(heading);
        DivVerifyBase<int32_t, int32_t>("int32_int32", t);
        t.print(std::cout);
    }

    {
        Table<uint32_t, uint32_t> t(heading);
        DivVerifyBase<uint32_t, uint32_t>("uint32_uint32", t);
        t.print(std::cout);
    }

    {
        Table<int64_t, int64_t> t(heading);
        DivVerifyBase<int64_t, int64_t>("int64_int64", t);
        t.print(std::cout);
    }

    {
        Table<uint64_t, uint64_t> t(heading);
        DivVerifyBase<uint64_t, uint64_t>("uint64_uint64", t);
        t.print(std::cout);
    }

    // all Overflow.h division combinations covered
}
