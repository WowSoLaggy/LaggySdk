#pragma once


namespace Sdk
{

  template <typename Id>
  class Registry
  {
  public:
    Id create() { return d_nextId++; }

    template <class C>
    C& add(const Id i_id, const C& i_component)
    {
      return storage<C>()[i_id] = i_component;
    }

    template <class C>
    C* find(const Id i_id)
    {
      auto& container = storage<C>();
      const auto it = container.find(i_id);
      return it != container.end() ? &it->second : nullptr;
    }
    template <class C>
    const C* find(const Id i_id) const
    {
      const auto& container = storage<C>();
      const auto it = container.find(i_id);
      return it != container.end() ? &it->second : nullptr;
    }

    template <class C>
    C& get(const Id i_id)
    {
      auto* comp = find<C>(i_id);
      CONTRACT_ASSERT(comp, "Component not found");
      return *comp;
    }
    template <class C>
    const C& get(const Id i_id) const
    {
      const auto* comp = find<C>(i_id);
      CONTRACT_ASSERT(comp, "Component not found");
      return *comp;
    }

    template <class C>
    std::unordered_map<Id, C>& all()
    {
      return storage<C>();
    }
    template <class C>
    const std::unordered_map<Id, C>& all() const
    {
      return storage<C>();
    }

    void remove(const Id i_id)
    {
      for (auto& [_, poolPtr] : d_pools)
        poolPtr->erase(i_id);
    }

  private:
    Id d_nextId = 1;

    struct IPool
    {
      virtual ~IPool() = default;
      virtual void erase(Id) = 0;
    };

    template<class C>
    struct Pool : IPool
    {
      std::unordered_map<Id, C> data;
      void erase(Id id) override { data.erase(id); }
    };

    std::unordered_map<std::type_index, std::unique_ptr<IPool>> d_pools;

    template <class C>
    std::unordered_map<Id, C>& storage()
    {
      const auto key = std::type_index(typeid(C));
      auto& poolPtr = d_pools[key];
      if (!poolPtr)
        poolPtr = std::make_unique<Pool<C>>();
      return static_cast<Pool<C>*>(poolPtr.get())->data;
    }

    template <class C>
    const std::unordered_map<Id, C>* storage() const
    {
      const auto key = std::type_index(typeid(C));
      const auto it = d_pools.find(key);
      if (it == d_pools.end())
        return nullptr;
      return &static_cast<Pool<C>*>(it->second.get())->data;
    }
  };

} // ns Sdk
