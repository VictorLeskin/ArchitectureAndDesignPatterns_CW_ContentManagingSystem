///************************* OUTS HOMEWORK ****************************************

#include "cComponentRegistry.hpp"
#include "cIoC.hpp"

std::unique_ptr<iComponent> cComponentRegistry::createComponent(const std::string& type)
{
    try {
        // ��������� ����������� ����� IoC ���������
        auto component = container_.Resolve<iComponent>( scope_, type);
        if (component) {
            return std::unique_ptr<iComponent>( component );
        }
    }
    catch (...) {
        // ����������� ������
    }
    return nullptr;
}
