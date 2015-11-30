#include "camera_tower_controller.h"

extern "C" {
void* getInstance () {
    return new TowerController();
}
}
