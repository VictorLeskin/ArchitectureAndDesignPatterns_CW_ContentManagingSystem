///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "ArchitectureAndDesignPatterns_CW_ContentManagingSystem.hpp"

// gTest grouping class
class test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem : public ArchitectureAndDesignPatterns_CW_ContentManagingSystem
  {
  public:
    // add here members for free access.
    using ArchitectureAndDesignPatterns_CW_ContentManagingSystem::ArchitectureAndDesignPatterns_CW_ContentManagingSystem; // delegate constructors
  };

};
 
TEST_F(test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem, test_ctor )
{
  Test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem t;
}

