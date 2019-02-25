add_subdirectory(factories)

add_to_target(awRuntime PUBLIC resourceManager.hpp)
add_to_target(awRuntime PUBLIC resourceRegistry.hpp)
add_to_target(awRuntime INTERFACE resourceManager.inl)
add_to_target(awRuntime INTERFACE resourceRegistry.inl)
