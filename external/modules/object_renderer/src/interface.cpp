#include "object_renderer.h"

extern "C" {
void* getInstance () {
    return new ObjectRenderer();
}
}
