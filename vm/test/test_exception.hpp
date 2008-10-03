#include "builtin/exception.hpp"
#include "object_types.hpp"
#include "exception.hpp"

#include <cxxtest/TestSuite.h>

using namespace rubinius;

class TestException : public CxxTest::TestSuite {
  public:

  VM *state;

  void setUp() {
    state = new VM();
  }

  void tearDown() {
    delete state;
  }

  void test_exception_fields() {
    TS_ASSERT_EQUALS(2U, Exception::fields);
  }

  void test_type_error_raise() {
    object_type type = ClassType;
    OBJECT obj = G(object);

    TS_ASSERT_THROWS(TypeError::raise(type, obj, "failed"), const TypeError &);
  }

  void test_type_error_raise_without_reason() {
    object_type type = ClassType;
    OBJECT obj = G(object);

    TS_ASSERT_THROWS(TypeError::raise(type, obj), const TypeError &);
  }

  void test_assertion_raise() {
    TS_ASSERT_THROWS(Assertion::raise("failed"), const Assertion &);
  }

  void test_ruby_exception_argument_error() {
    TS_ASSERT_THROWS_ASSERT(Exception::argument_error(state, 1, 2),
        const RubyException &e,
        TS_ASSERT(Exception::argument_error_p(state, e.exception)));
    TS_ASSERT_THROWS_ASSERT(Exception::argument_error(state, "failed"),
        const RubyException &e,
        TS_ASSERT(Exception::argument_error_p(state, e.exception)));
  }

  void test_make_type_error() {
    object_type type = ClassType;
    OBJECT obj = G(object);

    TS_ASSERT(Exception::type_error_p(state,
          Exception::make_type_error(state, type, obj)));
  }

  void test_ruby_exception_type_error() {
    object_type type = ClassType;
    OBJECT obj = G(object);

    TS_ASSERT_THROWS_ASSERT(Exception::type_error(state, type, obj),
        const RubyException &e,
        TS_ASSERT(Exception::type_error_p(state, e.exception)));
    TS_ASSERT_THROWS_ASSERT(Exception::type_error(state, "failed"),
        const RubyException &e,
        TS_ASSERT(Exception::type_error_p(state, e.exception)));
  }

  void test_ruby_exception_float_domain_error() {
    TS_ASSERT_THROWS_ASSERT(Exception::float_domain_error(state, "failed"),
        const RubyException &e,
        TS_ASSERT(Exception::float_domain_error_p(state, e.exception)));
  }

  void test_ruby_exception_zero_division_error() {
    TS_ASSERT_THROWS_ASSERT(Exception::zero_division_error(state, "failed"),
        const RubyException &e,
        TS_ASSERT(Exception::zero_division_error_p(state, e.exception)));
  }

  void test_ruby_exception_assertion_error() {
    TS_ASSERT_THROWS_ASSERT(Exception::assertion_error(state, "failed"),
        const RubyException &e,
        TS_ASSERT(Exception::assertion_error_p(state, e.exception)));
  }

  void test_ruby_exception_object_bounds_exceeded_error() {
    TS_ASSERT_THROWS_ASSERT(
        Exception::object_bounds_exceeded_error(state, G(object), 1U),
        const RubyException &e,
        TS_ASSERT(Exception::object_bounds_exceeded_error_p(state, e.exception)));
  }
};
