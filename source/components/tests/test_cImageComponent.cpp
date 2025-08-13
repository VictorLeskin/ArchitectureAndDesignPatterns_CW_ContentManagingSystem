///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cImageComponent.hpp"

// gTest grouping class
class test_cImageComponent : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cImageComponent : public cImageComponent
  {
  public:
    // add here members for free access.
    using cImageComponent::cImageComponent; // delegate constructors
  };

};
 
TEST_F(test_cImageComponent, test_ctor )
{
  Test_cImageComponent t;
}

