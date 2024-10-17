int getTemp()
{
    const float MAX_DIST = 10.0;
    SensorType[S2] = sensorEV3_Ultrasonic;
    float distance = 0.0;
    int temp_p = 0;
    distance = SensorValue[S2];

    temp_p = (distance / MAX_DIST) * 100;

    return temp_p;
}
