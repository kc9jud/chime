cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(chime LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compiler options
add_compile_options(
  $<$<CONFIG:Release>:-O3>
  $<$<CONFIG:Debug>:-Wall>
  $<$<CONFIG:Debug>:-Wextra>
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-ggdb>
)

find_package(OpenMP QUIET)
find_package(Eigen3 REQUIRED)
find_package(GSL REQUIRED)

find_package(MKL)
if(TARGET MKL::MKL)
  target_link_libraries(Eigen3::Eigen INTERFACE MKL::MKL)
  target_compile_definitions(Eigen3::Eigen INTERFACE EIGEN_USE_MKL_ALL)
else()
  find_package(BLAS)
  if(TARGET BLAS::BLAS)
    target_link_libraries(Eigen3::Eigen INTERFACE BLAS::BLAS)
    target_compile_definitions(Eigen3::Eigen INTERFACE EIGEN_USE_BLAS)
  endif()
endif()

if(TARGET OpenMP::OpenMP_CXX)
  target_link_libraries(Eigen3::Eigen INTERFACE OpenMP::OpenMP_CXX)
endif()

add_subdirectory(libraries/mcutils)
add_subdirectory(libraries/am)
add_subdirectory(libraries/basis)
add_subdirectory(libraries/basis_func)
add_subdirectory(libraries/quadpp)

add_subdirectory(programs)

# ##############################################################################
# define installation rules
# ##############################################################################
install(
  EXPORT chimeTargets
  NAMESPACE chime::
  FILE chimeTargets.cmake
  DESTINATION lib/cmake/chime)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/chimeConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/chime"
  NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO)
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/chimeConfigVersion.cmake"
  VERSION "${chime_VERSION_MAJOR}.${chime_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion)

# install the configuration file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/chimeConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/chimeConfigVersion.cmake
        DESTINATION lib/cmake/chime)

export(
  EXPORT chimeTargets
  NAMESPACE chime::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/chimeTargets.cmake")
