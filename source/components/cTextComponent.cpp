///************************* OUTS HOMEWORK ****************************************

#include "cTextComponent.hpp"

void cTextComponent::initialize(const nlohmann::json& params)
{
  content = params.value("content", "Default text");
  color = params.value("color", "#000000");
  fontSize = params.value("fontSize", 16);
}

std::string cTextComponent::render() const 
{
  return "<div style=\"color: " + color + "; font-size: " +
    std::to_string(fontSize) + "px;\">" + content + "</div>";
}

nlohmann::json cTextComponent::getParametersSchema() 
{
  return {
      {"type", "object"},
      {"properties", 
    {
          {"content", {
              {"type", "string"},
              {"description", "Text content"}
          }},
          {"color", {
              {"type", "string"},
              {"description", "Text color in hex format"},
              {"default", "#000000"}
          }},
          {"fontSize", {
              {"type", "integer"},
              {"description", "Font size in pixels"},
              {"default", 16}
          }}
      }},
      {"required", {"content"}}
  };
}
