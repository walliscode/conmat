# Create the conmat library
add_library(conmat STATIC
  conmat.cpp
  conmat.h
)

target_include_directories(conmat PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Require C++23
target_compile_features(conmat PUBLIC cxx_std_23)

# Create a test executable (not exported)
add_executable(conmat_demo
  demo.cpp
)

target_link_libraries(conmat_demo PRIVATE
  conmat
)
