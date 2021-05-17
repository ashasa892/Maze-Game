#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;	

using ComponentId = std::size_t;

inline ComponentId getComponentTypeId() {
	static ComponentId lastId = 0;
	return lastId++;
}

template<typename T> inline ComponentId getComponentTypeId() noexcept {
	static ComponentId typeId = 0;
	return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}

	virtual ~Component() {}

};


class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitset componentBitset;

public:
	void update()
	{
		for(auto& c : components) {
			c->update();
		}
		for(auto& c : components) {
			c->render();
		}

	}

	void render() {}
	bool isActive() const {return active;}
	void destroy() { active = false;}

	template<typename T> bool hasComponent() const 
	{
		return componentBitset[getComponentTypeId<T>()];
	}
	
	template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{c};
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeId<T>()] = c;
		componentBitset[getComponentTypeId<T>()] = true;

		c->init();
		return *c;
	} 

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeId<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto &e : entities) e->update();
	}

	void render()
	{
		for (auto &e : entities) e->render();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{e};
		entities.emplace_back(std::move(uPtr));
		return* e;
	}
	
};