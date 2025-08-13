///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cHeaderComponent.hpp"

// gTest grouping class
class test_cHeaderComponent : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cHeaderComponent : public cHeaderComponent
  {
  public:
    // add here members for free access.
    using cHeaderComponent::cHeaderComponent; // delegate constructors
  };

};
 
TEST_F(test_cHeaderComponent, test_ctor )
{
  Test_cHeaderComponent t;
}

