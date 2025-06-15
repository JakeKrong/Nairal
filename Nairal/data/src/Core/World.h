#pragma once
#include "Types.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include <memory>

class World {
public:
	void Init();

	Entity CreateEntity();
	void DestroyEntity(Entity entity);

	template<typename T>
	//To register component type with ComponentManager
	void RegisterComponent() {
		m_ComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	//Add component data to ComponentManager & update entity's bit signature to include componenet
	//System Manager to re-evaluate systems needed to track entity
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
	ComponentType GetComponentType(Entity entity) {
		return m_ComponentManager->GetComponentType<T>(entity);
	}

	template<typename T>
	Ref<T> RegisterSystem() {
		return m_SystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature) {
		m_SystemManager->SetSignature<T>(signature);
	}

private:
	Scope<ComponentManager> m_ComponentManager;
	Scope<EntityManager> m_EntityManager;
	Scope<SystemManager> m_SystemManager;
};