///************************* OUTS HOMEWORK ****************************************
#ifndef CREQUESTACCESSTOPAGE_HPP
#define CREQUESTACCESSTOPAGE_HPP

#include "cUser.hpp"
#include "cPageId.hpp"

class cRequestAccessToPage
{
public:
	cRequestAccessToPage(cUser& user, cPageId& pageId) : user(user), pageId(pageId)
	{
	}

public:
	cUser user;
	cPageId pageId;
	std::string token;
};

#endif //#ifndef CREQUESTACCESSTOPAGE_HPP
