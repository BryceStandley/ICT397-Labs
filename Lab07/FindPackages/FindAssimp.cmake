find_library(ASSIMP_LIBRARY
        NAMES libassimp.5.0.0.dylib
        HINTS "${PROJECT_SOURCE_DIR}/vender/assimp/5.0.1"
        PATHS ${PROJECT_SOURCE_DIR}/vender/assimp/5.0.1
        PATH_SUFFIXES lib
        NO_DEFAULT_PATH
        )

if(ASSIMP_LIBRARY)
    message("Library: ASSIMP found! Located at: ${ASSIMP_LIBRARY}")
else()
    message("Library: ASSIMP NOT found! Located at: ${ASSIMP_LIBRARY}")
endif(ASSIMP_LIBRARY)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/vender/assimp/5.0.1/include)