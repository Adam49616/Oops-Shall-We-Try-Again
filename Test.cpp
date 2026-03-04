#define CATCH_CONFIG_MAIN

#if defined(__has_include)
#if __has_include("catch.hpp")
#include "catch.hpp"
#elif __has_include("catch_amalgamated.hpp")
#include "catch_amalgamated.hpp"
#elif __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#elif __has_include(<catch2/catch_test_macros.hpp>)
#include <catch2/catch_test_macros.hpp>
#else
// Fallback stub when Catch2 headers are not available.
// This implements minimal TEST_CASE / REQUIRE behavior and a main runner
// so the existing tests can compile and run.
#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>

namespace catch_stub {
    inline std::vector<std::function<void()>>& tests() {
        static std::vector<std::function<void()>> t;
        return t;
    }
    inline void register_test(std::function<void()> f) {
        tests().push_back(std::move(f));
    }
}

// Helper macros to create unique names using __LINE__ (same value within a single expansion)
#define CTOKENPASTE(a,b) a##b
#define CTOKENPASTE2(a,b) CTOKENPASTE(a,b)
#define UNIQUE_NAME(base) CTOKENPASTE2(base, __LINE__)

// Define TEST_CASE macro
#define TEST_CASE(name) \
      static void UNIQUE_NAME(_test_)(); \
      static int UNIQUE_NAME(_reg_) = (catch_stub::register_test([]()->void{ UNIQUE_NAME(_test_)(); }), 0); \
      static void UNIQUE_NAME(_test_)()

// Simple REQUIRE macro
#define REQUIRE(expr) \
      do { \
        if (!(expr)) { \
          std::cerr << "REQUIRE failed: " << #expr << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
          std::exit(EXIT_FAILURE); \
        } \
      } while (0)

// Remove this block — **do not provide a main() here**, Catch2 already generates main()
#endif
#else
#error "__has_include not supported by this compiler. Add Catch2 include path or manually include the correct Catch header."
#endif

#include <sstream>
#include <iostream>
#include "validate.h"

TEST_CASE("Valid input")
{
    std::istringstream input("25\n");
    std::ostringstream output;

    std::streambuf* cinBackup = std::cin.rdbuf(input.rdbuf());
    std::streambuf* coutBackup = std::cout.rdbuf(output.rdbuf());

    int result = getValidatedInt(0, 100, "Enter value: ", "Invalid");

    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    REQUIRE(result == 25);
}