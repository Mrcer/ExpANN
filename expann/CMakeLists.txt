set(EXPANN_SRC
    dummy.cpp
)

set(EXPANN_HEADERS
    utils.hpp
    expann.hpp
)

add_library(expann ${EXPANN_SRC})
target_include_directories(expann PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)