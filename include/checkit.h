#ifndef CHECKIT_H
#define CHECKIT_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <limits>
#include <typeinfo>
#include <iomanip>


class CheckIt {

    int num_assertions{0};
    int num_failed{0};
    std::ostream& errfile;

public:

    CheckIt(std::ostream &errfile) : errfile(errfile) {}

    int fprint_summary(std::ostream& out, const std::string& label)
    {
        out << label;
        out << "Assertions: " << num_assertions << "    Failures: " << num_failed << std::endl;
        return num_failed > 0;
    }

    int print_summary(const std::string& label)
    {
        return fprint_summary(std::cerr, label);
    }

    int print_summary(void)
    {
        return fprint_summary(std::cerr, "");
    }

    void log_failure(const std::string &details, const char* filename, int linenumber,
                     const std::string& msg)
    {
        errfile << "* failure:  " << details << "\n";
        errfile << "  location: " << filename << ":" << linenumber << "\n";
        errfile << "  message:  " << msg << std::endl;
    }

    void assert_true(int value, const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (!value) {
            num_failed += 1;
            std::ostringstream ss;
            ss << "value is not true: " << value;
            auto details = ss.str();
            log_failure(details, filename, linenumber, msg);
        }
    }

    // Floating point comparison
    template<typename FP>
    void assert_equal_fp(FP value1, FP value2,
                         const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (value1 != value2) {
            num_failed += 1;
            std::ostringstream ss;
            ss << "floating point (type " << typeid(FP).name() << ") not equal: "
               << std::setprecision(std::numeric_limits<FP>::max_digits10)
               << value1 << " ≠ " << value2;
            auto details = ss.str();
            log_failure(details, filename, linenumber, msg);
        }
    }

    // Integer comparision
    template<typename Integer>
    void assert_equal_integer(Integer value1, Integer value2,
                              const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (value1 != value2) {
            num_failed += 1;
            std::ostringstream ss;
            ss << "integers not equal: " << value1 << " ≠ " << value2;
            auto details = ss.str();
            log_failure(details, filename, linenumber, msg);
        }
    }

    void assert_equal_char(char value1, char value2,
                           const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (value1 != value2) {
            num_failed += 1;
            std::ostringstream ss;
            ss << "chars not equal: '" << value1 << "' ≠ '" << value2 << "'";
            auto details = ss.str();
            log_failure(details, filename, linenumber, msg);
        }
    }

    void assert_equal_pointer(void *value1, void *value2,
                              const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (value1 != value2) {
            num_failed += 1;
            log_failure("pointer values not equal", filename, linenumber, msg);

        }
    }

    void assert_equal_cstr(const char *value1, const char *value2,
                           const std::string& msg, const char *filename, int linenumber)
    {
        num_assertions += 1;
        if (strcmp(value1, value2) != 0) {
            num_failed += 1;
            std::ostringstream ss;
            ss << "cstr values not equal: '" << value1 << "' ≠ '" << value2 << "'";
            auto details = ss.str();
            log_failure(details, filename, linenumber, msg);
        }
    }
};


#define check_true(A, B, C)              A .assert_true(B, C, __FILE__, __LINE__)
#define check_equal_pointer(A, B, C, D)  A .assert_equal_pointer(B, C, D, __FILE__, __LINE__)
#define check_equal_cstr(A, B, C, D)     A .assert_equal_cstr(B, C, D, __FILE__, __LINE__)
#define check_equal_fp(A, B, C, D)       A .assert_equal_fp(B, C, D, __FILE__, __LINE__)
#define check_equal_integer(A, B, C, D)  A .assert_equal_integer(B, C, D, __FILE__, __LINE__)
#define check_equal_char(A, B, C, D)     A .assert_equal_char(B, C, D, __FILE__, __LINE__)

#endif
