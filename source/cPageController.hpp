///************************* OUTS HOMEWORK ****************************************
#ifndef CPAGECONTROLLER_HPP
#define CPAGECONTROLLER_HPP

#include "cComponentRegistry.hpp"
#include "cAuthServer.hpp"
#include <nlohmann/json.hpp>
#include <vector>

class cPageController {
public:
    cPageController(cComponentRegistry& registry, cAuthServer& auth)
        : registry_(registry), auth_(auth) {
    }

    struct PageResponse {
        std::string html;
        bool access_denied;
    };

    PageResponse renderPage(const std::string pageId, const std::string& authToken) const {
        auto authResult = auth_.validateToken(authToken, pageId );
        if (!authResult) {
            return { "", true };
        }

        // Здесь должна быть логика загрузки страницы из БД
        nlohmann::json page = loadPageFromDb(pageId);

        //if (!checkPermissions(authResult.role, page["permissions"]["read"])) {
        //    return { "", true };
        //}

        std::string html;
        for (const nlohmann::json& component : page["components"]) {
            auto comp = registry_.createComponent(component["type"]);
            if (comp) {
                html += comp->render(component["parameters"]);
            }
        }

        return { html, false };
    }

private:
    cComponentRegistry& registry_;
    cAuthServer& auth_;

    nlohmann::json loadPageFromDb(const std::string pageId) const {
        // Реальная реализация должна загружать из БД
        return {
            {"id", pageId},
            {"permissions", {
                {"read", {"*"}},
                {"write", {"admin", "editor"}}
            }},
            {"components", {
                {
                    {"type", "header"},
                    {"parameters", {
                        {"text", "Welcome"},
                        {"level", 1}
                    }}
                },
                {
                    {"type", "text"},
                    {"parameters", {
                        {"content", "Sample content"}
                    }}
                }
            }}
        };
    }

    bool checkPermissions(const std::string& role, const nlohmann::json& allowedRoles) const {
        for (const auto& r : allowedRoles) {
            if (r == "*" || r == role) return true;
        }
        return false;
    }
};

#endif //#ifndef CPAGECONTROLLER_HPP
