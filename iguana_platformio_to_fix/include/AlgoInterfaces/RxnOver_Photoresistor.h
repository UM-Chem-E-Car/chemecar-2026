#pragma once


#include "Utility/Sensor.h"
#include "Utility/Filter.h"


class RxnOver_Photoresistor
{
public:


    RxnOver_Photoresistor() : valueFilter(Filter()), derFilter(Filter()), derivative(DDx()), triggers_hit(0), STORED_REACTION_DATA(-1){}

    bool verifyReactionDone(const Light_Sensor::Data& data, const double& time){
        double value = data.value;
        double avg_value = valueFilter.newAverage(value);
        double delta_value = derivative.change(value);
        double avg_delta_value = derFilter.newAverage(delta_value);

        if (abs(avg_delta_value) < TRIGGER_VALUE){
            triggers_hit++;
            // Logger::instance().log("TRIGGER HITS: " + String(triggers_hit));
            if (triggers_hit >= TRIGGER_COUNT){
                STORED_REACTION_DATA = time;
                return true;
            }
        }
    return false;
    }

    const double getReactionData() {
        // if (STORED_REACTION_DATA == -1){Logger::instance().log("INVALID REACTION DATA", Logger::LogType::ERROR);}
        return STORED_REACTION_DATA;
    };

private:
    const double TRIGGER_VALUE = .001;
    const double TRIGGER_COUNT = 3;

    Filter valueFilter;
    Filter derFilter;
    DDx derivative;

    int triggers_hit;

    double STORED_REACTION_DATA;
};