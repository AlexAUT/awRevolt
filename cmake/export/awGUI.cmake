install(TARGETS
        awGUI
        EXPORT awGUIConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       awGUI
       NAMESPACE aw::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/awGUIConfig.cmake"
)
install(EXPORT
        awGUIConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/aw/cmake"
        NAMESPACE aw::
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/aw/gui" # source directory
        DESTINATION "include/aw" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
        PATTERN "*.inl" # select inline files
)

