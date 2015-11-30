set(SOURCES
    "src/camera_tower_controller.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/camera_tower_controller.h"
)

include_directories(include)
add_library(camera_tower_controller MODULE ${SOURCES} ${HEADERS})
target_link_libraries(camera_tower_controller PRIVATE lmscore)
