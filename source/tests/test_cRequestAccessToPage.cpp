///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cRequestAccessToPage.hpp"

// gTest grouping class
class test_cRequestAccessToPage : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cRequestAccessToPage : public cRequestAccessToPage
  {
  public:
    // add here members for free access.
    using cRequestAccessToPage::cRequestAccessToPage; // delegate constructors
  };

};
 
TEST_F(test_cRequestAccessToPage, test_ctor )
{
  cUser user;
  cPageId pageId;
  Test_cRequestAccessToPage t(user,pageId);
}

