///************************* OUTS HOMEWORK ****************************************
#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

class iComponent
{
public:

  virtual ~iComponent() = default;

  // Инициализация компонента с параметрами
  virtual void initialize(const nlohmann::json& params) = 0;

  // Рендеринг компонента в HTML
  virtual std::string render() const = 0;
  virtual std::string render(const nlohmann::json& parameters) const  = 0;

  // Получение типа компонента
  virtual std::string getType() const = 0;

  // Получение схемы параметров (для UI)
  static nlohmann::json getParametersSchema();
};

// Функция для создания экземпляра компонента 
extern std::shared_ptr<iComponent> createComponent();

#endif //#ifndef ICOMPONENT_HPP
