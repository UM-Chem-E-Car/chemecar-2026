#pragma once

class TimeRun_Linear{
public:
    TimeRun_Linear() : STORED_TIME(-1){}

    void calculate(double distance){
        STORED_TIME = (CAR_A * distance + CAR_B) * 1000;
    }
    double getTimeRun(){
        return STORED_TIME;
    }

private:
    const double CAR_A = 4;
;
    const double CAR_B = -1.8512;

    double STORED_TIME;
};