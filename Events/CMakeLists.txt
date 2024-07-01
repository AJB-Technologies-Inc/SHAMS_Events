
add_library(ShamsEvents)

set_target_properties(ShamsEvents PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(ShamsEvents PRIVATE
    src/events.cpp
    src/types/eventQueue.cpp
)

target_link_libraries(ShamsEvents
    RingBuffer
    Dictionary
    Buffer
)

target_include_directories(ShamsEvents PRIVATE ./src)
target_include_directories(ShamsEvents PUBLIC ./includes)

# Install
install(TARGETS ShamsEvents
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)