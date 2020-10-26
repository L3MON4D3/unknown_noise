add_executable(unknown_noise
    main.cpp
)

target_link_libraries(unknown_noise PUBLIC fastNoise)
target_link_libraries(unknown_noise PUBLIC PkgConfig::Cairomm)
