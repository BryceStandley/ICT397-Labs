cmake_minimum_required(VERSION 3.17)
project(Lab07)
set(CMAKE_CXX_STANDARD 14)

# Setting Find cmake files path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/FindPackages)




# Define the executable.
add_executable(${PROJECT_NAME} ${SOURCES})

# Adding Source Directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Adding GLM include as it doesnt have a library
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vender/glm/0.9.9.8/include)


# Unsetting old cache var's
unset(${GLAD_LIBRARY} CACHE)
unset(${ASSIMP_LIBRARY} CACHE)
unset(${GLFW_LIBRARY} CACHE)

# Finding required lib's using FindXXX.cmake files in /cmakeFiles
message("")
find_package(OpenGL REQUIRED)
find_package(GLAD REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(GLFW REQUIRED)
message("")



# Linking lib files to compiler
target_link_libraries(${PROJECT_NAME} ${GLAD_LIBRARY} ${ASSIMP_LIBRARY} ${GLFW_LIBRARY})

# Copy resource files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${PROJECT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res )