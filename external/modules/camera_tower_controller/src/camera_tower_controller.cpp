#include "camera_tower_controller.h"
#include "lms/math/vertex.h"
#include <cmath>
#include <cstdint>
bool TowerController::initialize() {
    cameraTowerControlls = writeChannel<sensor_utils::Car>("TOWER");
    servoHorizontal = 0;
    servoVertical = 0;
    verticalState = 0;
    lastCycle = lms::extra::PrecisionTime::now();
    return true;
}

bool TowerController::deinitialize() {
    return true;
}

bool TowerController::cycle() {
    sensor_utils::Car::State state;

    float minServoHor = config().get<float>("minServoHor");
    float maxServoHor = config().get<float>("maxServoHor");
    float minServoVer = config().get<float>("minServoVer");
    float maxServoVer = config().get<float>("maxServoVer");

    for(const std::string &msg : messaging()->receive("car")) {
        if(msg == "left") {
            verticalState = -1;
        } else if(msg == "right") {
            verticalState = 1;
        } else if(msg == "acc_down") {
            verticalState = 1;
        } else if(msg == "acc_up") {
            verticalState = 0;
        } else if(msg == "break_down") {
            verticalState = -1;
        } else if(msg == "break_up") {
            verticalState = 0;
        } else if(msg == "right_up" || msg == "left_up") {
            servoHorizontal = 0;
        }
    }

    float t = lms::extra::PrecisionTime::since(lastCycle).toFloat();
    servoVertical = servoVertical + verticalState * config().get<float>("v") * t;
    servoHorizontal = servoHorizontal + verticalState * config().get<float>("v") * t;

    servoVertical = std::max(float(minServoVer), std::min(servoVertical, float(maxServoVer)));
    servoHorizontal = std::max(float(minServoHor), std::min(servoVertical, float(maxServoHor)));

    state.name = "keyboard";
    state.steering_front = servoHorizontal;
    state.steering_rear = servoVertical;
    cameraTowerControlls->putState(state);

    logger.debug() << servoVertical << " " << servoHorizontal;

    lastCycle = lms::extra::PrecisionTime::now();
    return true;
}
