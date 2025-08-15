///************************* OUTS HOMEWORK ****************************************
#ifndef CPAGECONTROLLER_HPP
#define CPAGECONTROLLER_HPP

#include "cComponentRegistry.hpp"
#include "cAuthServer.hpp"
#include "cJSONDataBase.hpp"

#include <nlohmann/json.hpp>
#include <vector>

class cPageController 
{
public:
    cPageController(cms::cJSONDataBase& db, cAuthServer& auth, cComponentRegistry& registry)
        : db_(db), registry_(registry), auth_(auth) {
    }

    struct PageResponse {
        std::string html;
        bool access_denied;
    };

    PageResponse renderPage(const cRequestAccessToPage& req);

protected:
    cms::cJSONDataBase& db_;
    cComponentRegistry& registry_;
    cAuthServer& auth_;

    bool checkPermissions(const std::string& role, const nlohmann::json& allowedRoles) const {
        for (const auto& r : allowedRoles) {
            if (r == "*" || r == role) return true;
        }
        return false;
    }
};

#endif //#ifndef CPAGECONTROLLER_HPP
