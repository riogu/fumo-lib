add_executable(fumo_usage usage.c)
target_include_directories(fumo_usage PRIVATE ${PROJECT_SOURCE_DIR}/src)

add_executable(fumo_safe_access safe_access.c)
target_include_directories(fumo_safe_access PRIVATE ${PROJECT_SOURCE_DIR}/src)
