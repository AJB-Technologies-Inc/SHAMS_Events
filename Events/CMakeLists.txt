
add_library(ShamsEvents INTERFACE)

set_target_properties(ShamsEvents PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(ShamsEvents INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/event.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/delegate.hpp>
)

target_link_libraries(ShamsEvents
    INTERFACE
    Buffer
)
target_include_directories(ShamsEvents INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
)

# Install
install(TARGETS ShamsEvents
    EXPORT ShamsEventTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT ShamsEventTargets
    FILE ShamsEventTargets.cmake
    DESTINATION lib/cmake/ShamsEvent
)