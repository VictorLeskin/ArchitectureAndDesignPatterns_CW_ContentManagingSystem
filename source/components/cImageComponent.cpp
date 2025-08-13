///************************* OUTS HOMEWORK ****************************************

#include "cImageComponent.hpp"

void cImageComponent::initialize(const nlohmann::json& params) {
    src = params.value("src", "");
    altText = params.value("alt", "");
    width = params.value("width", -1);
    height = params.value("height", -1);
}

std::string cImageComponent::render() const {
    std::string style;
    if (width > 0) style += "width: " + std::to_string(width) + "px;";
    if (height > 0) style += "height: " + std::to_string(height) + "px;";
    
    return "<img src=\"" + src + "\" alt=\"" + altText + "\"" +
           (style.empty() ? "" : " style=\"" + style + "\"") + ">";
}

nlohmann::json cImageComponent::getParametersSchema() {
    return {
        {"type", "object"},
        {"properties", {
            {"src", {
                {"type", "string"},
                {"description", "Image URL or path"},
                {"format", "uri"}
            }},
            {"alt", {
                {"type", "string"},
                {"description", "Alternative text"},
                {"default", ""}
            }},
            {"width", {
                {"type", "integer"},
                {"description", "Image width in pixels"},
                {"minimum", 1},
                {"default", -1}
            }},
            {"height", {
                {"type", "integer"},
                {"description", "Image height in pixels"},
                {"minimum", 1},
                {"default", -1}
            }}
        }},
        {"required", {"src"}}
    };
}

