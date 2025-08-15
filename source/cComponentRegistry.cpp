///************************* OUTS HOMEWORK ****************************************

#include "cComponentRegistry.hpp"
#include "cIoC.hpp"

inline std::unique_ptr<iComponent> cComponentRegistry::createComponent(const std::string& type)
{
    try {
        // Разрешаем зависимость через IoC контейнер
        auto component = container_.Resolve<iComponent>( scope_, type);
        if (component) {
            return std::unique_ptr<iComponent>( component );
        }
    }
    catch (...) {
        // Логирование ошибки
    }
    return nullptr;
}
