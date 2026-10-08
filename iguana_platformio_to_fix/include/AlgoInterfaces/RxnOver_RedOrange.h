#pragma once

#include "Utility/Sensor.h"
#include "Utility/Filter.h"



struct TimeAndRegimeData {

    double time_reaction_end;
    double reaction_end_value;

    TimeAndRegimeData() : time_reaction_end(-1), reaction_end_value(-1){};
    bool operator==(const TimeAndRegimeData& rhs) const {
        if (time_reaction_end != rhs.time_reaction_end)
            return false;
        if (reaction_end_value != rhs.reaction_end_value)
            return false;
        return true;
    }
};

class RxnOver_RedOrange{ 
    class CONSTS{
        const int TRIGGER_COUNT = 3;
        //0.001737
        const double TRIGGER_VALUE = 0.01737;
    };
public:

    typedef Color_Sensor::Data SensorData;
    typedef TimeAndRegimeData RxnData;

    RxnOver_RedOrange();

    bool verifyReactionDone(const SensorData& data, const double& time);
    const RxnData& getReactionData();

private:
    Filter valueFilter;
    Filter derFilter;
    DDx derivative;

    int triggers_hit;

    RxnData STORED_REACTION_DATA;
};