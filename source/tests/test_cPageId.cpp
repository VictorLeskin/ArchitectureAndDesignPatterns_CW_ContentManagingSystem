///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cPageId.hpp"

// gTest grouping class
class test_cPageId : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cPageId : public cPageId
  {
  public:
    // add here members for free access.
    using cPageId::cPageId; // delegate constructors
  };

};
 
TEST_F(test_cPageId, test_ctor )
{
  Test_cPageId t;
}

