
add_library(ShamsEvents)

target_sources(ShamsEvents PRIVATE
    src/eventManager.cpp
)

target_include_directories(ShamsEvents PRIVATE ./src)
target_include_directories(ShamsEvents PUBLIC .)