#pragma once

#include <aw/utils/typeHelper/trueFalseTypes.hpp>

#include <memory>
#include <string>
#include <vector>

namespace aw
{
template <typename Factory, typename ResourceType>
class ResourceFactory
{
public:
  using TypePtr = std::shared_ptr<ResourceType>;

public:
  template <typename... Args>
  TypePtr create(std::string_view name, Args&&... args)
  {
    return static_cast<Factory*>(this)->create(std::forward<Args>(args)...);
  }

private:
private:
};

} // namespace aw
