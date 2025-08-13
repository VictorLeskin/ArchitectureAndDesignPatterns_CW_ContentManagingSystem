///************************* OUTS HOMEWORK ****************************************

#include "cHeaderComponent.hpp"

void cHeaderComponent::initialize(const nlohmann::json& params) {
  text = params.value("text", "Default Header");
  level = std::clamp(params.value("level", 1), 1, 6);
  alignment = params.value("alignment", "left");
}

std::string cHeaderComponent::render() const {
  return "<h" + std::to_string(level) +
    " style=\"text-align: " + alignment + ";\">" +
    text + "</h" + std::to_string(level) + ">";
}

nlohmann::json cHeaderComponent::getParametersSchema() {
  return {
      {"type", "object"},
      {"properties", {
          {"text", {
              {"type", "string"},
              {"description", "Header text"}
          }},
          {"level", {
              {"type", "integer"},
              {"description", "Header level (1-6)"},
              {"minimum", 1},
              {"maximum", 6},
              {"default", 1}
          }},
          {"alignment", {
              {"type", "string"},
              {"description", "Text alignment"},
              {"enum", {"left", "center", "right"}},
              {"default", "left"}
          }}
      }},
      {"required", {"text"}}
  };
}
