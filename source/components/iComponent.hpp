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

  // ������������� ���������� � �����������
  virtual void initialize(const nlohmann::json& params) = 0;

  // ��������� ���������� � HTML
  virtual std::string render() const = 0;
  virtual std::string render(const nlohmann::json& parameters) const  = 0;

  // ��������� ���� ����������
  virtual std::string getType() const = 0;

  // ��������� ����� ���������� (��� UI)
  static nlohmann::json getParametersSchema();
};

// ������� ��� �������� ���������� ���������� 
extern std::shared_ptr<iComponent> createComponent();

#endif //#ifndef ICOMPONENT_HPP
