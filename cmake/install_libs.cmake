# fetch libs from github
include(FetchContent)

FetchContent_Declare(
    shams_utilities
    GIT_REPOSITORY https://github.com/AJB-Technologies-Inc/SHAMS_Utilities.git
    GIT_TAG main
)

FetchContent_MakeAvailable(shams_utilities)