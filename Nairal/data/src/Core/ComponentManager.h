#pragma once
#include "Types.h"
#include <array>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <cassert>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity enitity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	//Inserts component into an Entity (stores in next free index, updates maps)
	void InsertData(Entity entity, T component) {
		assert(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end() && "Component added to same entity more than once.");

		size_t newIndex = m_Size;
		m_EntityToIndexMap[entity] = newIndex;
		m_IndexToEntityMap[newIndex] = entity;
		m_ComponentArray[newIndex] = component;
		++m_Size;
	}

	//Swaps last componenet into removed slot
	void RemoveData(Entity entity) {
		assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Removing non-existent component");

		size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
		size_t indexOfLastElement = m_Size - 1;
		m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

		Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
		m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_EntityToIndexMap.erase(entity);
		m_IndexToEntityMap.erase(indexOfLastElement);

		--m_Size;
	}

	T& GetData(Entity entity) {
		assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Retrieving a non-existant componenet.");
		return m_ComponentArray[m_EntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override{
		if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			RemoveData(entity);
	}

private:
	std::array<T, MAX_ENTITIES> m_ComponentArray{};
	std::unordered_map<Entity, size_t> m_EntityToIndexMap{}; //Maps Entity to index
	std::unordered_map<size_t, Entity> m_IndexToEntityMap{}; //Maps index to Entity
	size_t m_Size{};
};

class ComponentManager {
public:
	template<typename T>
	void RegisterComponent() {
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering component type more than once.");

		m_ComponentArrays.insert({ typeName, std::make_shared <ComponentArray<T>>() });
		m_ComponentTypes.insert({ typeName, m_NextComponentType });

		++m_NextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType() {
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		return m_ComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity) {
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity) {
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity) {
		for (auto const& pair : m_ComponentArrays) {
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> m_ComponentTypes{}; //For mapping ComponentType to unique ID
	std::unordered_map<const char*, Ref<IComponentArray>> m_ComponentArrays{}; //Maps type name to component arrays
	ComponentType m_NextComponentType{}; //Tracks next unused ID

	template<typename T>
	Ref<ComponentArray<T>> GetComponentArray() {
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Componenet not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
	}
};