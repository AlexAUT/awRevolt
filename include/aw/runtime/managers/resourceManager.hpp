#pragma once

#include <memory>
#include <unordered_map>

namespace aw
{
template <typename Type>
class ResourceManager
{
public:
  using TypePtr = std::shared_ptr<Type>;

public:
  bool has(std::string_view name) const;
  Type* get(std::string_view name);
  const Type* get(std::string_view name) const;

  TypePtr set(std::string name, TypePtr newObj);

private:
private:
  std::unordered_map<std::string, TypePtr> mContainer;
};

template <typename Type>
bool ResourceManager<Type>::has(std::string_view name) const
{
  return mContainer.find(name.data()) != mContainer.end();
}

template <typename Type>
Type* ResourceManager<Type>::get(std::string_view name)
{
  return const_cast<Type*>(const_cast<const ResourceManager<Type>*>(this)->get(name.data()));
}

template <typename Type>
const Type* ResourceManager<Type>::get(std::string_view name) const
{
  auto found = mContainer.find(name.data());
  if (found != mContainer.end())
    return found->second.get();
  return nullptr;
}

template <typename Type>
auto ResourceManager<Type>::set(std::string name, TypePtr newObj) -> TypePtr
{
  mContainer[name] = newObj;
  return newObj;
}
} // namespace aw
