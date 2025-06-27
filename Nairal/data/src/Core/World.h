#pragma once
#include "../Core/Types.h"
#include "../Core/EntityManager.h"
#include "../Core/ComponentManager.h"
#include "../Core/SystemManager.h"
#include <memory>

class World {
public:
    World()
        : m_ComponentManager(std::make_unique<ComponentManager>()),
        m_EntityManager(std::make_unique<EntityManager>()),
        m_SystemManager(std::make_unique<SystemManager>()) {
    }

    // Move Constructor
    World(World&& other) noexcept
        : m_ComponentManager(std::move(other.m_ComponentManager)),
        m_EntityManager(std::move(other.m_EntityManager)),
        m_SystemManager(std::move(other.m_SystemManager)) {
    }

    void Init();

    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    template<typename T>
    void RegisterComponent() {
        m_ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        m_ComponentManager->RemoveComponent<T>(entity);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);
        m_EntityManager->SetSignature(entity, signature);

        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return m_ComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return m_ComponentManager->GetComponentType<T>();
    }

    template<typename T>
    Ref<T> RegisterSystem() {
        return m_SystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature) {
        m_SystemManager->SetSignature<T>(signature);
    }

    template<typename T>
    bool HasComponent(Entity entity) {
        try {
            m_ComponentManager->GetComponent<T>(entity);
            return true;
        }
        catch (...) {
            return false;
        }
    }

private:
    Scope<ComponentManager> m_ComponentManager;
    Scope<EntityManager> m_EntityManager;
    Scope<SystemManager> m_SystemManager;
};