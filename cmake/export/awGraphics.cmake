install(TARGETS
        awGraphics
        EXPORT awGraphicsConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       awGraphics
       NAMESPACE aw::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/awGraphicsConfig.cmake"
)
install(EXPORT
        awGraphicsConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/aw/cmake"
        NAMESPACE aw::
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/aw/graphics" # source directory
        DESTINATION "include/aw" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "*.inl" # select inline files
)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/aw/opengl" # source directory
        DESTINATION "include/aw" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "*.inl" # select inline files
)

