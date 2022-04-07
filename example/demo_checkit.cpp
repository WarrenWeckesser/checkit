
#include <cstdint>
#include "checkit.h"


int main(void)
{
    float x = 3.0;
    double z = 2.4;
    double third = 1.0/3.0;
    long double r = 1.2345e33;

    uint16_t u = 2311;
    long long t = 349898923843L;
    char c = 'X';

    CheckIt test = CheckIt(std::cerr);

    check_true(test, 1, "should be true");
    check_true(test, 0, "intentional fail");

    check_equal_cstr(test, "hello", "not hello", "intentional fail");
    check_equal_cstr(test, "this", "this", "should be the same");

    check_equal_fp(test, x, 3.1f, "another intentional failure");
    check_equal_fp(test, z, 99.25, "one more");
    check_equal_fp(test, third, 1 - 2.0/3.0, "expect to fail");
    check_close_fp(test, third, 1 - 2.0/3.0, 1.5e-17, "expect to fail");
    check_close_fp(test, third, 1 - 2.0/3.0, 5e-16, "should pass");
    check_equal_fp(test, r, 9.87e32L, "a long double check");

    check_equal_integer(test, u, (uint16_t) 2300, "failed uint16_t check");
    check_equal_integer(test, u, (uint16_t) 2311, "should pass");
    check_equal_integer(test, t, -1LL, "should fail");

    check_equal_char(test, c, 'Z', "should fail");



    return test.print_summary("SUMMARY: ");
}