#pragma once

#include "EventHandler.h"
#include "SdkFwd.h"


namespace Sdk
{
  class Registry : public EventHandler
  {
  public:
    EntityId create() { return d_nextId++; }

    template <class C>
    void add(const EntityId i_id, const C& i_component)
    {
      storage<C>()[i_id] = i_component;
    }

    template <class C>
    C* find(const EntityId i_id)
    {
      auto& container = storage<C>();
      const auto it = container.find(i_id);
      return it != container.end() ? &it->second : nullptr;
    }
    template <class C>
    const C* find(const EntityId i_id) const
    {
      const auto* container = storage<C>();
      if (!container)
        return nullptr;
      const auto it = container->find(i_id);
      return it != container->end() ? &it->second : nullptr;
    }

    template <class C>
    C& get(const EntityId i_id)
    {
      auto* comp = find<C>(i_id);
      CONTRACT_ASSERT(comp, "Component not found");
      return *comp;
    }
    template <class C>
    const C& get(const EntityId i_id) const
    {
      const auto* comp = find<C>(i_id);
      CONTRACT_ASSERT(comp, "Component not found");
      return *comp;
    }

    template <class C>
    std::unordered_map<EntityId, C>& all()
    {
      return storage<C>();
    }
    template <class C>
    const std::unordered_map<EntityId, C>& all() const
    {
      if (const auto* container = storage<C>())
        return *container;
      static const std::unordered_map<EntityId, C> empty;
      return empty;
    }

    void remove(const EntityId i_id)
    {
      for (auto& [_, poolPtr] : d_pools)
        poolPtr->erase(i_id);
    }

  private:
    EntityId d_nextId = 1;

    struct IPool
    {
      virtual ~IPool() = default;
      virtual void erase(EntityId i_id) = 0;
    };

    template<class C>
    struct Pool : IPool
    {
      std::unordered_map<EntityId, C> data;
      void erase(EntityId i_id) override { data.erase(i_id); }
    };

    std::unordered_map<std::type_index, std::unique_ptr<IPool>> d_pools;

    template <class C>
    std::unordered_map<EntityId, C>& storage()
    {
      const auto key = std::type_index(typeid(C));
      auto& poolPtr = d_pools[key];
      if (!poolPtr)
        poolPtr = std::make_unique<Pool<C>>();
      return static_cast<Pool<C>*>(poolPtr.get())->data;
    }

    template <class C>
    const std::unordered_map<EntityId, C>* storage() const
    {
      const auto key = std::type_index(typeid(C));
      const auto it = d_pools.find(key);
      if (it == d_pools.end())
        return nullptr;
      return &static_cast<Pool<C>*>(it->second.get())->data;
    }
  };

} // ns Sdk
