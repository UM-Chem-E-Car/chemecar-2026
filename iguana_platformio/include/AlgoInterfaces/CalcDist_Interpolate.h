#pragma once

#include "AlgoInterfaces/CustomDataType/TimeData.h"

class CalcDist_Interpolate{
public:

    CalcDist_Interpolate() : STORED_DISTANCE(-1) {}

    void calculate(const ValueDiff& reactionSummary){
        double slope = (D_HIGH-D_LOW) / (T_HIGH-T_LOW);
        STORED_DISTANCE = -slope * (reactionSummary.diff - T_LOW) + D_HIGH;
    }

    double getDistance() {
        return STORED_DISTANCE;
    }

private:

    const double T_HIGH = 60000;
    const double T_LOW = 20000;

    const double D_HIGH = 30;
    const double D_LOW = 15;


    double STORED_DISTANCE;
};