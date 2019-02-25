install(TARGETS
        awRuntime
        EXPORT awRuntimeConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       awRuntime
       NAMESPACE aw::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/awRuntimeConfig.cmake"
)
install(EXPORT
        awRuntimeConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/aw/cmake"
        NAMESPACE aw::
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/aw/runtime" # source directory
        DESTINATION "include/aw" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "*.inl" # select inline files
)

