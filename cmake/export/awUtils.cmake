install(TARGETS
        awUtils
        EXPORT awUtilsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       awUtils
       NAMESPACE aw::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/awUtilsConfig.cmake"
)
install(EXPORT
        awUtilsConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/aw/cmake"
        NAMESPACE aw::
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/aw/utils" # source directory
        DESTINATION "include/aw" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "*.inl" # select inline files
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/aw/config.hpp
        DESTINATION "include/aw"
)

