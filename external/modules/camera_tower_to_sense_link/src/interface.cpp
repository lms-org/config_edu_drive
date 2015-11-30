#include "camera_tower_to_sense_link.h"

extern "C" {
void* getInstance () {
    return new TowerToSenseLink();
}
}
