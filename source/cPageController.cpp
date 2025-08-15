///************************* OUTS HOMEWORK ****************************************

#include "cPageController.hpp"
#include "cJSONDataBase.hpp"

cPageController::PageResponse cPageController::renderPage(const cRequestAccessToPage& req)
{
    const std::string pageId = req.pageId.id;
    const std::string authToken = req.token;

    auto authResult = auth_.validateToken(authToken, pageId);
    if (!authResult) {
        return { "", true };
    }

    // Load page from database
    std::optional<cms::Page> p = db_.getPageById(pageId);
    if( false == p.has_value() )
        return { "", true };

    const cms::Page& page = p.value();

    std::string html;
    for (auto component : page.components)
    {
        auto comp = registry_.createComponent(component.type);
        if (comp) {
            {
                comp->initialize(component.parameters);
                html += comp->render();
            }
        }
    }

    return { html, false };
}

