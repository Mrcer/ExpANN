set(EXPANN_SRC
    expann.cpp
    utils.cpp
)

set(EXPANN_HEADERS
    utils.h
    expann.h
)

add_library(expann ${EXPANN_SRC})
target_include_directories(expann PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)