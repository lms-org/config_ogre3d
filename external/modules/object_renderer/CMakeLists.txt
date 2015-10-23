set(SOURCES
    "src/object_renderer.cpp"
    "src/interface.cpp"
)

set(HEADERS
    "include/object_renderer.h"
)

include_directories(include)
add_library(object_renderer MODULE ${SOURCES} ${HEADERS})
target_link_libraries(object_renderer PRIVATE lmscore ogre_binding ogre_window_manager)
