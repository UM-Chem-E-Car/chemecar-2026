#pragma once

#include "Utility/Sensor.h"
#include "Utility/Filter.h"
#include "AlgoInterfaces/CustomDataType/TimeData.h"


class RxnOver_RedOrange{
public:

    typedef Color_Sensor::Data SensorData;

    RxnOver_RedOrange() : valueFilter(Filter()), derFilter(Filter()), derivative(DDx()), triggers_hit(0), STORED_REACTION_DATA(){}

    void setInitialValues(void* values){

    }

    bool verifyReactionDone(const SensorData& data, const double& time){
        double value = data.r / data.o;
        double avg_value = valueFilter.newAverage(value);
        double delta_value = derivative.change(value);
        double avg_delta_value = derFilter.newAverage(delta_value);

        if (abs(avg_delta_value) < TRIGGER_VALUE){
            triggers_hit++;
            if (triggers_hit >= TRIGGER_COUNT){
                STORED_REACTION_DATA.time_reaction_end = time;
                return true;
            }
        }
        return false;
    }

    const TimeData& getReactionData(){
        return STORED_REACTION_DATA;
    }

private:
    const int TRIGGER_COUNT = 3;
    //0.001737
    const double TRIGGER_VALUE = 0.01737;

    Filter valueFilter;
    Filter derFilter;
    DDx derivative;

    int triggers_hit;

    TimeData STORED_REACTION_DATA;
};