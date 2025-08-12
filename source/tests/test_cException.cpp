///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cException.hpp"

// gTest grouping class
class test_cException : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cException : public cException
  {
  public:
    // add here members for free access.
    using cException::cException; // delegate constructors
    using cException::szWhat;
  };

};
 
TEST_F(test_cException, test_ctor )
{
  const char* t0 = "Something wrong";
  Test_cException t(t0);
  EXPECT_EQ(t0, t.szWhat);
}


TEST_F(test_cException, test_what)
{
  const char* t0 = "Something wrong";
  Test_cException t(t0);
  EXPECT_EQ(t0, t.what());
}

