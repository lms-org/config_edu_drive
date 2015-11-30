#include "camera_tower_to_sense_link.h"
#include "lms/math/vertex.h"
#include <cmath>
#include <cstdint>
bool TowerToSenseLink::initialize() {
    actuators = writeChannel<sense_link::Actuators>("ACTUATORS");
    cameraTowerControlls = readChannel<sensor_utils::Car>("TOWER");

    return true;
}

bool TowerToSenseLink::deinitialize() {
    return true;
}

bool TowerToSenseLink::cycle() {
    actuators->clear();
    sense_link::Servo s0;
    s0.angle = cameraTowerControlls->steeringFront();
    sense_link::Servo s1;
    s1.angle = cameraTowerControlls->steeringRear();
    actuators->set(sense_link::ActuatorType::SERVO,1,s0);
    actuators->set(sense_link::ActuatorType::SERVO,2,s1);
    sense_link::ActuatorData led;
    led.Led.value = 255;
    actuators->set(sense_link::ActuatorType::LED,1,led);
    return true;
}
