#ifndef TO_ARDUIONO_H
#define TO_ARDUIONO_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <ostream>
#include "lms/math/vertex.h"
#include "sense_link/datatypes.h"
#include "sense_link/actuators.h"
#include "sensor_utils/car.h"

class TowerController : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();
private:
    lms::WriteDataChannel<sensor_utils::Car> cameraTowerControlls;
    lms::extra::PrecisionTime lastCycle;
    float servoHorizontal;
    float servoVertical;
    int verticalState;
    int horizontalState;
};

#endif // TO_ARDUIONO_H
