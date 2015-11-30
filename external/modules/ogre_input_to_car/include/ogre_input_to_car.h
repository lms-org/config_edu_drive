#ifndef OGRE_INPUT_TO_CAR_H
#define OGRE_INPUT_TO_CAR_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <sensor_utils/car.h>

/**
 * @brief LMS module ogre_input_to_car
 **/
class OgreInputToCar : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
private:
    lms::extra::PrecisionTime lastCycle;

    lms::WriteDataChannel<sensor_utils::Car> car;

    float steering;
    float speed;
    int accelerationState;
};

#endif // OGRE_INPUT_TO_CAR_H
