#pragma once
#include "../Core/Types.h"
#include "../Systems/System.h"
#include <unordered_map>
#include <memory>
#include <typeinfo>

class SystemManager {
public:
    template<typename T>
    Ref<T> RegisterSystem() {
        const char* typeName = typeid(T).name();

        assert(m_Systems.find(typeName) == m_Systems.end() && "Registering system more than once.");

        auto system = CreateRef<T>();
        m_Systems.insert({ typeName, system });
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();

        assert(m_Systems.find(typeName) != m_Systems.end() && "System used before registered.");

        m_Signatures.insert({ typeName, signature });
    }

    void EntityDestroyed(Entity entity) {
        for (auto const& pair : m_Systems) {
            auto const& system = pair.second;
            system->m_Entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        for (auto const& pair : m_Systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_Signatures[type];

            if ((entitySignature & systemSignature) == systemSignature) {
                system->m_Entities.insert(entity);
            }
            else {
                system->m_Entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> m_Signatures{};
    std::unordered_map<const char*, Ref<System>> m_Systems{};
};