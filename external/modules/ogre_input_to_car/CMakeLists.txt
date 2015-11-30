set(SOURCES
    "src/ogre_input_to_car.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/ogre_input_to_car.h"
)

include_directories(include)
add_library(ogre_input_to_car MODULE ${SOURCES} ${HEADERS})
target_link_libraries(ogre_input_to_car PRIVATE lmscore sensor_utils)
