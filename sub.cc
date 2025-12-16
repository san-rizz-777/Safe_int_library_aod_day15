#include "./test_sub.h"
#include "Overflow.h"
#include <cstdint>
#include <initializer_list>
#include <string>

/* ============================================================
 * SUB DISPATCHERS — one per Overflow.h function
 * ============================================================ */

template<typename T, typename U>
struct SubDispatcher;

/* char */
template<> struct SubDispatcher<char, char> {
    static void run(char a, char b) {
        Overflow::safe_sub_char_char(a, b);
    }
};

/* unsigned char */
template<> struct SubDispatcher<unsigned char, unsigned char> {
    static void run(unsigned char a, unsigned char b) {
        Overflow::safe_sub_uchar_uchar(a, b);
    }
};

/* short */
template<> struct SubDispatcher<short, short> {
    static void run(short a, short b) {
        Overflow::safe_sub_short_short(a, b);
    }
};

/* unsigned short */
template<> struct SubDispatcher<unsigned short, unsigned short> {
    static void run(unsigned short a, unsigned short b) {
        Overflow::safe_sub_ushort_ushort(a, b);
    }
};

/* int */
template<> struct SubDispatcher<int, int> {
    static void run(int a, int b) {
        Overflow::safe_sub_int_int(a, b);
    }
};

/* unsigned int */
template<> struct SubDispatcher<unsigned int, unsigned int> {
    static void run(unsigned int a, unsigned int b) {
        Overflow::safe_sub_uint_uint(a, b);
    }
};

/* int32_t */
template<> struct SubDispatcher<int32_t, int32_t> {
    static void run(int32_t a, int32_t b) {
        Overflow::safe_sub_int32_int32(a, b);
    }
};

/* uint32_t */
template<> struct SubDispatcher<uint32_t, uint32_t> {
    static void run(uint32_t a, uint32_t b) {
        Overflow::safe_sub_uint32_uint32(a, b);
    }
};

/* int64_t */
template<> struct SubDispatcher<int64_t, int64_t> {
    static void run(int64_t a, int64_t b) {
        Overflow::safe_sub_int64_int64(a, b);
    }
};

/* uint64_t */
template<> struct SubDispatcher<uint64_t, uint64_t> {
    static void run(uint64_t a, uint64_t b) {
        Overflow::safe_sub_uint64_uint64(a, b);
    }
};

/* ============================================================
 * VERIFY BASE (repo-style, unchanged)
 * ============================================================ */

template<typename T, typename U>
class SubVerifyBase {
public:
    SubVerifyBase(const std::string& name, Table<T, U>& t) {
        TestSuite<T, U, Operation::Subtract> tests;

        for (const auto& c : tests.get_cases()) {
            bool success = true;
            try {
                SubDispatcher<T, U>::run(c.first(), c.second());
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

void TestSub::run() {
    std::initializer_list<std::string> heading(
        {"Subtraction", "x", "y", "Expected", "Verdict"}
    );

    {
        Table<char, char> t(heading);
        SubVerifyBase<char, char>("char_char", t);
        t.print(std::cout);
    }

    {
        Table<unsigned char, unsigned char> t(heading);
        SubVerifyBase<unsigned char, unsigned char>("uchar_uchar", t);
        t.print(std::cout);
    }

    {
        Table<short, short> t(heading);
        SubVerifyBase<short, short>("short_short", t);
        t.print(std::cout);
    }

    {
        Table<unsigned short, unsigned short> t(heading);
        SubVerifyBase<unsigned short, unsigned short>("ushort_ushort", t);
        t.print(std::cout);
    }

    {
        Table<int, int> t(heading);
        SubVerifyBase<int, int>("int_int", t);
        t.print(std::cout);
    }

    {
        Table<unsigned int, unsigned int> t(heading);
        SubVerifyBase<unsigned int, unsigned int>("uint_uint", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, int32_t> t(heading);
        SubVerifyBase<int32_t, int32_t>("int32_int32", t);
        t.print(std::cout);
    }

    {
        Table<uint32_t, uint32_t> t(heading);
        SubVerifyBase<uint32_t, uint32_t>("uint32_uint32", t);
        t.print(std::cout);
    }

    {
        Table<int64_t, int64_t> t(heading);
        SubVerifyBase<int64_t, int64_t>("int64_int64", t);
        t.print(std::cout);
    }

    {
        Table<uint64_t, uint64_t> t(heading);
        SubVerifyBase<uint64_t, uint64_t>("uint64_uint64", t);
        t.print(std::cout);
    }

    // all Overflow.h subtraction combinations covered
}
