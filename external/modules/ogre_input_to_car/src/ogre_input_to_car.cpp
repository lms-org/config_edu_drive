#include "ogre_input_to_car.h"

bool OgreInputToCar::initialize() {
    car = writeChannel<sensor_utils::Car>("CAR");

    steering = 0;
    speed = 0;
    accelerationState = 0;
    lastCycle = lms::extra::PrecisionTime::now();

    return true;
}

bool OgreInputToCar::deinitialize() {
    return true;
}

bool OgreInputToCar::cycle() {
    sensor_utils::Car::State state;

    for(const std::string &msg : messaging()->receive("car")) {
        if(msg == "left") {
            steering = M_PI / 8;
        } else if(msg == "right") {
            steering = - M_PI / 8;
        } else if(msg == "acc_down") {
            accelerationState = 1;
        } else if(msg == "acc_up") {
            accelerationState = 0;
        } else if(msg == "break_down") {
            accelerationState = -1;
        } else if(msg == "break_up") {
            accelerationState = 0;
        } else if(msg == "right_up" || msg == "left_up") {
            steering = 0;
        }
    }

    float t = lms::extra::PrecisionTime::since(lastCycle).toFloat();
    if(accelerationState != 0) {
        speed = speed + accelerationState * config().get<float>("acc") * t;
    } else {
        speed = 0;
    }

    speed = std::max(float(-1), std::min(speed, float(1)));

    state.name = "keyboard";
    state.steering_front = steering;
    state.steering_rear = - steering;
    state.targetSpeed = speed;
    car->putState(state);

    logger.error("SPEED") << speed;

    lastCycle = lms::extra::PrecisionTime::now();

    return true;
}
