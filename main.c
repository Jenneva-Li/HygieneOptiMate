#include "PC_FileIO.c"
TFileHandle fin;

const int MAX_TIME_COL = 3;
const int MAX_TIME_ROW = 2;
float Time_intervals[MAX_TIME_ROW][MAX_TIME_COL] = {{ 0, 0, 0 }, { 0, 0, 0 }};
string Mode[MAX_TIME_ROW] = { { " " }, { " " } };

void LoadData(TFileHandle fin, float *Temp_p, int num_time);
void dispense_soap();
void water_off();
int getTemp();
void update_handles(float temp_p);
void displayUpdate(string mode, float temp_p, int time);
void face_wash(float *Temp_p);
void brush_teeth(float *Temp_p);

task main()
{
 // soap sonic
 SensorType[S1] = sensorEV3_Ultrasonic;
 wait1Msec(50);
 // handles sonic
 SensorType[S2] = sensorEV3_Ultrasonic;
 wait1Msec(50);
 // temp sonic
 SensorType[S3] = sensorEV3_Ultrasonic;
 wait1Msec(50);
 nMotorEncoder[motorA] = 0;
 nMotorEncoder[motorB] = 0;
 bool fileOkay = openReadPC (fin, "pre_set_modes.txt");
 if (!fileOkay)
  {
   displayString (5, "Unable to open the file.");
   wait1Msec(5000);
  }
 else
  {
   float Temp_p[MAX_TIME_ROW] = { 0, 0 };
   int num_time = 0;
   LoadData (fin, Temp_p, num_time);
   time1[T1] = 0;
   time1[T2] = 0;
   time1[T3] = 0;

   bool first_time_soap = true;
   string mode;
   float temp_p = 25;
   int time = 0;
   bool hand_present = true;
   bool inTime = true;
   displayUpdate (mode, temp_p, time);
   while (time1[T1] < 300000.0) // mimic for 24hr
    {
     if (SensorValue[S1] > 10 && SensorValue[S1] < 15)
      {
       if (time1[T3] > 30000 || first_time_soap == true)
        {
         dispense_soap ();
         time1[T1] = 0;
         time1[T3] = 0;
         first_time_soap = false;
        }
      }
     if (SensorValue[S3] <= 20)
      {
       temp_p = getTemp();
       if (temp_p != -1)
        {
         time = 0;
         displayUpdate(mode, temp_p, time);
         time1[T1] = 0;
        }
      }
     if (SensorValue[S2] > 5 && SensorValue[S2] < 20 && temp_p != -1)
      {
       time1[T2] = 0;
       while (hand_present || inTime)
        {
         update_handles(temp_p);
         time1[T1] = 0;
         while (inTime)
          {
           while (time1[T2] < 20000)
            {
             time = (20000 - time1[T2]) / 1000.0;
             // soap dispenser
             if (SensorValue[S1] > 10 && SensorValue[S1] < 15)
              {
               if (time1[T3] > 30000 || first_time_soap == true)
                {
                 dispense_soap();
                 time1[T1] = 0;

                 time1[T3] = 0;
                 first_time_soap = false;
                }
              }

             // temp change
             if (SensorValue[S3] <= 20)
              {
               temp_p = getTemp();
              }
             wait1Msec(200);
             displayUpdate(mode, temp_p, time);
             update_handles(temp_p);
            }
           inTime = false;
          }
         time = 0;
         if (SensorValue[S1] > 10 && SensorValue[S1] < 15)
          {
           if (time1[T3] > 30000 || first_time_soap == true)
            {
             dispense_soap();
             time1[T1] = 0;
             time1[T3] = 0;
             first_time_soap = false;
            }
          }
         // temp change
         if (SensorValue[S3] <= 20)
          {
           temp_p = getTemp();
          }
         wait1Msec(200);
         displayUpdate(mode, temp_p, time);
         update_handles(temp_p);
         if (SensorValue[S2] > 5 && SensorValue[S2] < 20)
          {
           hand_present = true;
          }
         else
          {
           time1[T1] = 0;
           hand_present = false;
          }
        }
       water_off ();
      }
     else

      {
       hand_present = true;
       inTime = true;
      }
     if (getButtonPress (buttonDown))
      {
       int stored_temp = temp_p;
       face_wash (Temp_p);
       displayUpdate (mode, stored_temp, time);
       time1[T1] = 0;
      }
     if (getButtonPress (buttonUp))
      {
       int stored_temp = temp_p;
       brush_teeth (Temp_p);
       displayUpdate (mode, stored_temp, time);
       time1[T1] = 0;
      }
    }
  }
 closeFilePC (fin);
}

void LoadData (TFileHandle fin, float *Temp_p, int num_time)
{
 for (int index = 0; index < 2; index++)
  {
   readTextPC (fin, Mode[index]);
   int temp_value = 0;
   readIntPC (fin, temp_value);
   Temp_p[index] = temp_value;
   readIntPC (fin, num_time);
   for (int time_index = 0; time_index < num_time; time_index++)
    {
     readFloatPC (fin, Time_intervals[index][time_index]);
    }
  }
}

void displayUpdate (string mode, float temp_p, int time)
{
 const int WIDTH = 177;
 const int HEIGHT = 127;
 const int ORIGIN = 1;
 string name;

 eraseDisplay();


 // full page rectangle
 drawRect(ORIGIN, HEIGHT, WIDTH, ORIGIN);

 // line between
 drawLine((WIDTH / 2) - 10, HEIGHT, (WIDTH / 2) - 10, ORIGIN); // vertical
 drawLine(ORIGIN, HEIGHT / 2, (WIDTH / 2) - 10, HEIGHT / 2);   // horizontal

 // brush teeth text
 displayBigStringAt(7, HEIGHT - 10, "Brush");
 displayBigStringAt(7, HEIGHT - 40, "Teeth");

 // face wash text
 displayBigStringAt(12, ORIGIN + 20, "Face");
 displayBigStringAt(12, ORIGIN + 50, "Wash");

 // temp bar
 drawRect(WIDTH - 20, HEIGHT - 23, WIDTH - 10, ORIGIN + 25);
 fillRect(WIDTH - 20, (ORIGIN + 25) + 77*(temp_p / 100.0), WIDTH - 10,
          ORIGIN + 25);

 // temp percent display
 displayStringAt(WIDTH - 20, ORIGIN + 15, "%d%c", temp_p, '%');

 // countdown display
 displayBigStringAt(WIDTH / 2 + 10, HEIGHT / 2, "%d%c", time, 's');
 if (mode == "brush_teeth")
  {
   name = "brushing teeth";

   // pressed
   displayInverseBigStringAt(7, HEIGHT - 10, "Brush");
   displayInverseBigStringAt(7, HEIGHT - 40, "Teeth");

   // unpressed
   displayBigStringAt(12, ORIGIN + 20, "Face");
   displayBigStringAt(12, ORIGIN + 50, "Wash");
  }
 else if (mode == "wash_face")
  {
   name = "washing face";
   // pressed
   displayInverseBigStringAt(12, ORIGIN + 20, "Face");
   displayInverseBigStringAt(12, ORIGIN + 50, "Wash");
   // unpressed
   displayBigStringAt(7, HEIGHT - 10, "Brush");
   displayBigStringAt(7, HEIGHT - 40, "Teeth");
  }
 else

  {
   name = "hand washing";

   // unpressed
   // brush
   displayBigStringAt(7, HEIGHT - 10, "Brush");
   displayBigStringAt(7, HEIGHT - 40, "Teeth");

   // face
   displayBigStringAt(12, ORIGIN + 20, "Face");
   displayBigStringAt(12, ORIGIN + 50, "Wash");
  }

 // mode name display
 displayStringAt(WIDTH / 2, HEIGHT - 10, name);
}

int getTemp()
{
 const float MAX_DIST = 20.0;
 SensorType[S3] = sensorEV3_Ultrasonic;
 float temp_p = -1;
 float distance = SensorValue[S3];
 if (distance <= 20.0)
  {
   temp_p = (distance / MAX_DIST) * 100;
   wait1Msec (200);
  }
 return temp_p;
}

void dispense_soap()
{
 const int STARTPOS = 0;
 const int ENDPOS = 150;
 nMotorEncoder[motorC] = 0;
 motor[motorC] = 25;
 while (nMotorEncoder[motorC] < ENDPOS)
  {
   if (nMotorEncoder[motorC] >= ENDPOS)
    {
     motor[motorC] = 0;
    }
   wait1Msec(10);
  }
 wait1Msec(50);
 motor[motorC] = -10;
 while (nMotorEncoder[motorC] > STARTPOS)

  {
   if (nMotorEncoder[motorC] <= STARTPOS)
    {
     motor[motorC] = 0;
    }
   wait1Msec(10);
  }
 motor[motorC] = 0;
}

void update_handles(float temp_p)
{
 int hot_encoder = 0;
 int cold_encoder = 0;
 if (temp_p >= 50)
  {
   hot_encoder = -170;
   cold_encoder = ((100.0 - temp_p) / 50.0) * -170.0;
  }
 else
  {
   cold_encoder = -170;
   hot_encoder = (temp_p / 50.0) * -170.0;
  }
 setMotorTarget(motorA, hot_encoder, 10);
 setMotorTarget(motorB, cold_encoder, 10);
 waitUntilMotorStop(motorB);
 waitUntilMotorStop(motorA);
}

void water_off()
{
 motor[motorA] = motor[motorB] = 10; // sets faucet motors to -10 motor power
 while (abs (nMotorEncoder[motorA]) > 0 && abs (nMotorEncoder[motorB]) > 0)  
 {}
 if (abs (nMotorEncoder[motorA])
     > 0) // checking if motorA has reached initial position
  {
   motor[motorB] = 0;
   while (abs (nMotorEncoder[motorA]) > 0)
   {}
   motor[motorA] = 0;
  }
 else if (abs (nMotorEncoder[motorB]) > 0)
  {
   motor[motorA] = 0;
   while (abs (nMotorEncoder[motorB]) > 0)    
   {}

   motor[motorB] = 0;
  }
 else
  {
   motor[motorA] = motor[motorB] = 0; // sets faucet motors to 0
  }
}

void brush_teeth (float *Temp_p)
{
 int mode_index = 0;
 for (int i = 0; i < MAX_TIME_ROW; i++)
  {
   if (Mode[i] == "brush_teeth")
    {
     mode_index = i;
     i = 2;
    }
  }
 time1[T2] = 0;
 int time_index = 0;
 while (time_index < 3) // 3 time intervals for brush teeth
  {
   float input_time = 0;
   update_handles (Temp_p[mode_index]);
   string mode = "brush_teeth";
   time1[T2] = 0;
   float time = time1[T2]; // array is in seconds
   while (time <= Time_intervals[mode_index][time_index])
    {
     input_time = Time_intervals[mode_index][time_index] - time;
     displayUpdate (mode, Temp_p[mode_index], input_time / 1000);
     wait1Msec(1000);
     time = time1[T2];
    };
   ++time_index;
   water_off();
   if (time_index < 3)
    {
     time1[T2] = 0;
     time = time1[T2];
     while (time <= Time_intervals[mode_index][time_index])
      {
       input_time = Time_intervals[mode_index][time_index] - time;
       displayUpdate (mode, Temp_p[mode_index], input_time / 1000);
       wait1Msec(1000);
       time = time1[T2];
      };

     time_index++;
     update_handles (Temp_p[mode_index]);
    }
   if (time_index < 3)
    {
     time1[T2] = 0;
     time = time1[T2];
     while (time <= Time_intervals[mode_index][time_index])
      {
       input_time = Time_intervals[mode_index][time_index] - time;
       displayUpdate (mode, Temp_p[mode_index], input_time / 1000);
       wait1Msec(1000);
       time = time1[T2];
      }
     ++time_index;
     water_off();
    }
   if (time_index < 3)
    {
     time1[T2] = 0;
     time = time1[T2];
     while (time <= Time_intervals[mode_index][time_index])
      {
       input_time = Time_intervals[mode_index][time_index] - time;
       displayUpdate (mode, Temp_p[mode_index], input_time / 1000);
       wait1Msec(1000);
       time = time1[T2];
      }
     time_index++;
    }
  }
}

void face_wash(int *Temp_p)
{
 int mode_index = 0;
 for (int i = 0; i < MAX_TIME_ROW; i++)
  {
   if (Mode[i] == "face_washing")
    {
     mode_index = i;
     i = 2;
    }
  }
 int time_index = 0;
 while (time_index < 3)
  {
   float input_time = 0;

   update_handles(Temp_p[mode_index]);
   string mode = "wash_face";
   time1[T2] = 0;
   float time = time1[T2];
   while (time <= Time_intervals[mode_index][time_index])
    {
     input_time = Time_intervals[mode_index][time_index] - time;
     displayUpdate (mode, Temp_p[mode_index],input_time / 1000); 
     time = time1[T2];
    }
   time_index++;
   water_off();
   if (time_index < 3)
    {
     time1[T2] = 0;
     time = time1[T2];
     while (time <= Time_intervals[mode_index][time_index])
      {
       input_time = Time_intervals[mode_index][time_index] - time;
       displayUpdate(mode, Temp_p[mode_index], input_time / 1000);
       wait1Msec(1000);
       time = time1[T2];
      }
     time_index++;
    }
  }
}
