///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cUser.hpp"

// gTest grouping class
class test_cUser : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cUser : public cUser
  {
  public:
    // add here members for free access.
    using cUser::cUser; // delegate constructors
  };

};
 
TEST_F(test_cUser, test_ctor )
{
  Test_cUser t("");
}

