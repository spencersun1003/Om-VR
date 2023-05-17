#include "mySensor.h"
MAX30105_sensor::MAX30105_sensor()
{   
    Serial.println("starting Wire...");
    Wire.begin();
    Serial.println("Initiating the sensor:MAX30105...");
    particleSensor = new MAX30105();
    setup();
}

void MAX30105_sensor::setup(){
    Serial.println("Settingup the sensor:MAX30105...");
    //while(1){
        Serial.println("Place your index finger on the sensor with steady pressure.");
        if (!particleSensor->begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
        {
            Serial.println("MAX30102 was not found. Please check wiring/power. ");
            delay(500);
        }
        else{
            Serial.print("MAX30102 found");
           //break;
        }
        particleSensor->setup(); //Configure sensor with default settings
        particleSensor->setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
        particleSensor->setPulseAmplitudeGreen(0); //Turn off Green LED
    //}

}
float MAX30105_sensor::getBPM(){
    return beatsPerMinute;
}


void MAX30105_sensor::read_data(){
    irValue = particleSensor->getIR();
    if (irValue>0){
        // for(int i=0;i<RATE_SIZE;i++){
        //     rates[i]=0;
        // }
        if (checkForBeat(irValue) == true)
        {
            Serial.println("A Heartbeat was found!");
            //We sensed a beat!
            long delta = millis() - lastBeat;
            lastBeat = millis();

            beatsPerMinute = 60 / (delta / 1000.0);

            if (beatsPerMinute < 255 && beatsPerMinute > 20)
            {
            rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
            rateSpot %= RATE_SIZE; //Wrap variable

            //Take average of readings
            beatAvg = 0;
            for (byte x = 0 ; x < RATE_SIZE ; x++)
                beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
            }
        }


        // Serial.print("IR=");
        // Serial.print(irValue);
        // Serial.print(", BPM=");
        // Serial.print(beatsPerMinute);
        // Serial.print(", Avg BPM=");
        // Serial.print(beatAvg);

        // if (irValue < 50000)
        //     Serial.print(" No finger?");

        // Serial.println();
    }
    else{

        Serial.println("MAX30105 not working, reatsrting...");
        setup();
    }
}


class GSR_Sensor{

    private:
        int gsr_value;
        int gsr_pin;
        int data[10]={0};
        int dataPointer=0;

    public:
        GSR_Sensor(int pin);
        void setup();
        void read_data();
        int get_filtereddata();

};

GSR_Sensor::GSR_Sensor(int pin=4)
{
    gsr_pin = pin;
    
}

void GSR_Sensor::setup(){
    Serial.println("Settingup the sensor:GSR...");
    pinMode(gsr_pin, INPUT);
}  

void GSR_Sensor::read_data(){
    float conductivevoltage;
    int GSRvalue;
    GSRvalue=analogRead(gsr_pin);
    data[dataPointer++]=GSRvalue;
    if(dataPointer==10)
    {
        dataPointer=0;
    }
    conductivevoltage = GSRvalue*(5.0/1023.0);

    // Serial.print("GsrValue=");
    Serial.println(GSRvalue);
}

int GSR_Sensor::get_filtereddata(){
    int sum=0;
    for(int i=0;i<10;i++)
    {
        sum+=data[i];
    }
    gsr_value=sum/10;
    return gsr_value;
}
