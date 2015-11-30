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

    float steeringAngle = config().get<float>("steeringAngle", M_PI/8);

    for(const std::string &msg : messaging()->receive("car")) {
        if(msg == "left") {
            steering = steeringAngle;
        } else if(msg == "right") {
            steering = - steeringAngle;
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

    float minSpeed = config().get<float>("minSpeed");
    float maxSpeed = config().get<float>("maxSpeed");

    speed = std::max(float(minSpeed), std::min(speed, float(maxSpeed)));

    state.name = "keyboard";
    state.steering_front = steering;
    state.steering_rear = - steering;
    state.targetSpeed = speed;
    car->putState(state);

    logger.debug() << speed << " " << steering;

    lastCycle = lms::extra::PrecisionTime::now();

    return true;
}
