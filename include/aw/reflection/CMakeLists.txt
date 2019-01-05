add_subdirectory(builtinTypes)
add_subdirectory(operations)

set(HEADER_FILES_REFLECTION ${HEADER_FILES_REFLECTION}
    ${CMAKE_CURRENT_SOURCE_DIR}/reflection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/typeDescriptor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/typeDescriptorClass.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/typeResolver.hpp
    PARENT_SCOPE)
