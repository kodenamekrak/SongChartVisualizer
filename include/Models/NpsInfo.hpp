struct NpsInfo {
    float Nps;
    float FromTime;
    float ToTime;

    NpsInfo();

    NpsInfo(float nps, float fromTime, float toTime)
    {
        Nps = nps;
        FromTime = fromTime;
        ToTime = toTime;
    }
};