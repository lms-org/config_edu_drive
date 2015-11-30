set(SOURCES
    "src/camera_tower_to_sense_link.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/camera_tower_to_sense_link.h"
)

include_directories(include)
add_library(camera_tower_to_sense_link MODULE ${SOURCES} ${HEADERS})
target_link_libraries(camera_tower_to_sense_link PRIVATE lmscore sense_link)
