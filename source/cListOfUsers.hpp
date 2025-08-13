///************************* OUTS HOMEWORK ****************************************
#ifndef CLISTOFUSERS_HPP
#define CLISTOFUSERS_HPP

#include <initializer_list>
#include <vector>
#include <string>
#include "cUser.hpp"

class cListOfUsers
{
public:
	cListOfUsers(std::initializer_list<cUser> list);

	std::vector<std::string> Users() const
	{
		std::vector<std::string> ret;
		for (const auto& u : users)
			ret.push_back(u.Name());
		return ret;
	}

	std::vector<cUser> users;
};

#endif //#ifndef CLISTOFUSERS_HPP
