add_subdirectory(file)
add_subdirectory(math)
add_subdirectory(messageBus)
add_subdirectory(spatial)
add_subdirectory(time)
add_subdirectory(typeHelper)

target_sources(awUtils
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/color.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/colors.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/log.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/stringFormat.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
)
