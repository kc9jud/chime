cmake_minimum_required(VERSION 3.15)

# ##############################################################################
# define library
# ##############################################################################

# add headers and sources
set(chime_headers chime.h constants.h tprme.h relative_rme.h relativecm_rme.h)
set(chime_sources relative_rme.cpp relativecm_rme.cpp)

# define chime library and add source files
add_library(chime ${chime_sources})
add_library(chime::chime ALIAS chime)
target_link_libraries(
  chime
  PUBLIC m basis::basis am::am
  PRIVATE basis_func::basis_func chime::chime Eigen3::Eigen)

# ##############################################################################
# define executables
# ##############################################################################

add_executable(relative-gen relative-gen.cpp)
add_executable(relativecm-gen relativecm-gen.cpp)

# ##############################################################################
# link dependencies
# ##############################################################################

target_link_libraries(
  relative-gen PRIVATE basis_func::basis_func chime::chime Eigen3::Eigen m
                       mcutils::mcutils quadpp::quadpp)
target_link_libraries(
  relativecm-gen PRIVATE basis_func::basis_func chime::chime Eigen3::Eigen m
                         mcutils::mcutils quadpp::quadpp)

if(TARGET OpenMP::OpenMP_CXX)
  target_link_libraries(relative-gen PRIVATE OpenMP::OpenMP_CXX)
  target_link_libraries(relativecm-gen PRIVATE OpenMP::OpenMP_CXX)
endif()

# ##############################################################################
# define installed targets
#
# actual installation is performed by top-level CMakeLists.txt
# ##############################################################################
install(TARGETS relative-gen relativecm-gen DESTINATION bin)

# ##############################################################################
# define include directory
# ##############################################################################
cmake_path(GET chime_SOURCE_DIR PARENT_PATH chime_PARENT_DIR)
target_include_directories(
  chime INTERFACE $<BUILD_INTERFACE:${chime_PARENT_DIR}>
                  $<INSTALL_INTERFACE:include>)

# ##############################################################################
# define installation rules
# ##############################################################################
install(
  TARGETS chime
  DESTINATION lib
  EXPORT chimeTargets)
install(FILES ${chime_headers} DESTINATION include/chime)
