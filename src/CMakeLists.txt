add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE fmt::fmt-header-only)
target_compile_features(main PRIVATE cxx_std_23)
