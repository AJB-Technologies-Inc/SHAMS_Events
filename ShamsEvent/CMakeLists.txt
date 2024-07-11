
add_library(ShamsEvent INTERFACE)

target_link_libraries(ShamsEvent
    INTERFACE
    Buffer
)
target_include_directories(ShamsEvent INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/shams>
)

# Install
install(TARGETS ShamsEvent
    EXPORT ShamsEventTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/shams
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/shams
    FILES_MATCHING PATTERN "*.hpp"
)

# Install the export targets
install(EXPORT ShamsEventTargets
    FILE ShamsEventTargets.cmake
    NAMESPACE Shams::
    DESTINATION lib/cmake/ShamsEvent
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/ShamsEventConfig.cmake.in"
    "ShamsEventConfig.cmake"
    INSTALL_DESTINATION lib/cmake/ShamsEvent
)

# Generate and install the config file for find_package()
write_basic_package_version_file(
    ShamsEventConfigVersion.cmake
    VERSION 1.0
    COMPATIBILITY AnyNewerVersion
)

# Install the generated ShamsEventConfig.cmake and ShamsEventConfigVersion.cmake
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ShamsEventConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ShamsEventConfigVersion.cmake"
    DESTINATION lib/cmake/ShamsEvent
)