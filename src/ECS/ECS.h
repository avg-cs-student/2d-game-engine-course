#pragma once

#include <algorithm>
#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

/**
 * Signature:
 *
 * We use a bitset to keep track of which components an entity has and also
 * helps keep track of which entities a system is interested in.
 */
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
protected:
	static int nextId;
};

/**
 * Used to assign a unique id to a component type.
 */
template <typename T>
class Component: public IComponent {
	static int GetId() {
		static auto id = nextId++;
		return id;
	}
};

class Entity {
private:
	int id;

public:
	Entity(int id): id(id) {};
	Entity(const Entity& entity) = default;
	int GetId() const;

	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& other) const { return id == other.id; }
	bool operator !=(const Entity& other) const { return id != other.id; }
	bool operator >(const Entity& other) const { return id > other.id; }
	bool operator <(const Entity& other) const { return id < other.id; }
};

/**
 * System:
 *
 * Processes entities that contain a specific signature.
 */
class System {
private:
	Signature componentSignature;

	/**
         * List of entites that the system is interested in.
         */
	std::vector<Entity> entities;

public:
	System() = default; 
	virtual ~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetCompoonentSignature() const;

	/*
	 * Defines the compoent type that entities must have to be required by
	 * the system.
	 */
	template <typename TComponent> void RequireComponent();
};

class Registry {
	// Todo: ...
};


template <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}
