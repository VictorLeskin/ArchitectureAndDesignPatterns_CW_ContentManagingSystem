///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cTextComponent.hpp"

// gTest grouping class
class test_cTextComponent : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cTextComponent : public cTextComponent
  {
  public:
    // add here members for free access.
    using cTextComponent::cTextComponent; // delegate constructors
  };

};
 
TEST_F(test_cTextComponent, test_ctor )
{
  Test_cTextComponent t;
}

