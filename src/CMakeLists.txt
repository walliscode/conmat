# Create the conmat library
add_library(conmat STATIC
  conmat.cpp
  conmat.h
)

# Add namespace alias for FetchContent compatibility
add_library(conmat::conmat ALIAS conmat)

# Use generator expressions for better FetchContent compatibility
target_include_directories(conmat PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# Require C++23
target_compile_features(conmat PUBLIC cxx_std_23)

# Only build demo if this is the top-level project
if(PROJECT_IS_TOP_LEVEL)
  # Create a demo executable (not exported)
  add_executable(conmat_demo
    demo.cpp
  )

  target_link_libraries(conmat_demo PRIVATE
    conmat::conmat
  )
endif()
