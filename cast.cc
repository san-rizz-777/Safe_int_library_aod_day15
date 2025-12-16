#include "./cast.h"
#include "Overflow.h"
#include <cstdint>
#include <initializer_list>
#include <string>

/* ============================================================
 * CAST DISPATCHERS — one per Overflow.h function
 * ============================================================ */

template<typename T, typename U>
struct CastDispatcher;

/* int64_t -> int32_t */
template<> struct CastDispatcher<int64_t, int32_t> {
    static void run(int64_t a) {
        Overflow::safe_cast_int32_int64(a);
    }
};

/* uint64_t -> int32_t */
template<> struct CastDispatcher<uint64_t, int32_t> {
    static void run(uint64_t a) {
        Overflow::safe_cast_int32_uint64(a);
    }
};

/* uint64_t -> int64_t */
template<> struct CastDispatcher<uint64_t, int64_t> {
    static void run(uint64_t a) {
        Overflow::safe_cast_int64_uint64(a);
    }
};

/* int32_t -> char */
template<> struct CastDispatcher<int32_t, char> {
    static void run(int32_t a) {
        Overflow::safe_cast_char_int32(a);
    }
};

/* int32_t -> short */
template<> struct CastDispatcher<int32_t, short> {
    static void run(int32_t a) {
        Overflow::safe_cast_short_int32(a);
    }
};

/* int64_t -> short */
template<> struct CastDispatcher<int64_t, short> {
    static void run(int64_t a) {
        Overflow::safe_cast_short_int64(a);
    }
};

/* int32_t -> unsigned char */
template<> struct CastDispatcher<int32_t, unsigned char> {
    static void run(int32_t a) {
        Overflow::safe_cast_uchar_int32(a);
    }
};

/* int32_t -> unsigned short */
template<> struct CastDispatcher<int32_t, unsigned short> {
    static void run(int32_t a) {
        Overflow::safe_cast_ushort_int32(a);
    }
};

/* int32_t -> uint32_t */
template<> struct CastDispatcher<int32_t, uint32_t> {
    static void run(int32_t a) {
        Overflow::safe_cast_uint32_int32(a);
    }
};

/* int64_t -> uint64_t */
template<> struct CastDispatcher<int64_t, uint64_t> {
    static void run(int64_t a) {
        Overflow::safe_cast_uint64_int64(a);
    }
};

/* uint32_t -> int32_t */
template<> struct CastDispatcher<uint32_t, int32_t> {
    static void run(uint32_t a) {
        Overflow::safe_cast_int32_uint32(a);
    }
};

/* ============================================================
 * VERIFY BASE (repo-style)
 * ============================================================ */

template<typename T, typename U>
class CastVerifyBase {
public:
    CastVerifyBase(const std::string& name, Table<T, U>& t) {
        TestSuite<T, U, Operation::Cast> tests;

        for (const auto& c : tests.get_cases()) {
            bool success = true;
            try {
                CastDispatcher<T, U>::run(c.first());
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

void TestCast::run() {
    std::initializer_list<std::string> heading(
        {"Cast", "x", "y", "Expected", "Verdict"}
    );

    {
        Table<int64_t, int32_t> t(heading);
        CastVerifyBase<int64_t, int32_t>("int64_to_int32", t);
        t.print(std::cout);
    }

    {
        Table<uint64_t, int32_t> t(heading);
        CastVerifyBase<uint64_t, int32_t>("uint64_to_int32", t);
        t.print(std::cout);
    }

    {
        Table<uint64_t, int64_t> t(heading);
        CastVerifyBase<uint64_t, int64_t>("uint64_to_int64", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, char> t(heading);
        CastVerifyBase<int32_t, char>("int32_to_char", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, short> t(heading);
        CastVerifyBase<int32_t, short>("int32_to_short", t);
        t.print(std::cout);
    }

    {
        Table<int64_t, short> t(heading);
        CastVerifyBase<int64_t, short>("int64_to_short", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, unsigned char> t(heading);
        CastVerifyBase<int32_t, unsigned char>("int32_to_uchar", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, unsigned short> t(heading);
        CastVerifyBase<int32_t, unsigned short>("int32_to_ushort", t);
        t.print(std::cout);
    }

    {
        Table<int32_t, uint32_t> t(heading);
        CastVerifyBase<int32_t, uint32_t>("int32_to_uint32", t);
        t.print(std::cout);
    }

    {
        Table<int64_t, uint64_t> t(heading);
        CastVerifyBase<int64_t, uint64_t>("int64_to_uint64", t);
        t.print(std::cout);
    }

    {
        Table<uint32_t, int32_t> t(heading);
        CastVerifyBase<uint32_t, int32_t>("uint32_to_int32", t);
        t.print(std::cout);
    }

    // ✔ all Overflow.h casting combinations covered
}
