# fetch libs from github
include(FetchContent)

# SHAMS Utilities Repository
FetchContent_Declare(
    shams_utilities
    GIT_REPOSITORY https://github.com/AJB-Technologies-Inc/SHAMS_Utilities.git
    GIT_TAG main
    GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(shams_utilities)

# Common CMake modules Repository
FetchContent_Declare(
    cmake_modules
    GIT_REPOSITORY https://github.com/AJB-Technologies-Inc/CmakeModules.git
    GIT_TAG main
    GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(cmake_modules)
include(${cmake_modules_SOURCE_DIR}/InstallAndExportShamsLib.cmake)