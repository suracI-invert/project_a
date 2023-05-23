#pragma once

#include<iostream>
#include<cassert>
#include<queue>
#include<unordered_map>
#include<bitset>
#include<array>
#include<memory>
#include<set>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 5000;
const ComponentType MAX_COMPONENTS = 32;
 
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity].reset();
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		mSignatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		return mSignatures[entity];
	}

private:
	std::queue<Entity> mAvailableEntities{};
	std::array<Signature, MAX_ENTITIES> mSignatures{};
	uint32_t mLivingEntityCount{};
};

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
		++mSize;
	}

	void RemoveData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mSize;
	}

	T& GetData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> mComponentArray{};
	std::unordered_map<Entity, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, Entity> mIndexToEntityMap{};
	size_t mSize{};
};

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		// assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
		mComponentTypes.insert({typeName, mNextComponentType});
		mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

		++mNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
	ComponentType mNextComponentType{};


	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};

class System
{
public:
	std::set<Entity> entities;
};

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		auto system = std::make_shared<T>();
		mSystems.insert({typeName, system});
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		mSignatures.insert({typeName, signature});
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;


			system->entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->entities.insert(entity);
			}
			else
			{
				system->entities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> mSignatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};

class Manager
{
public:
	void init()
	{
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	Entity CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<SystemManager> mSystemManager;
};