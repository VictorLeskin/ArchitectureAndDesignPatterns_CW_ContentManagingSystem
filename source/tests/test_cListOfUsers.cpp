///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cListOfUsers.hpp"

// gTest grouping class
class test_cListOfUsers : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cListOfUsers : public cListOfUsers
  {
  public:
    // add here members for free access.
    using cListOfUsers::cListOfUsers; // delegate constructors
  };

};
 
TEST_F(test_cListOfUsers, test_ctor )
{
  Test_cListOfUsers t({});
}

