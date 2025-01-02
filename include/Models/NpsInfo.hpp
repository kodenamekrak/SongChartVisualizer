#pragma once

struct NpsInfo {
    float Nps;
    float FromTime;
    float ToTime;

    NpsInfo() = default;

    NpsInfo(float nps, float fromTime, float toTime)
    {
        Nps = nps;
        FromTime = fromTime;
        ToTime = toTime;
    }
};