task main()
{

void water_off()
{
      motor[motorA] = motor[motorB] = 10; //sets faucet motors to -10 motor power
      while(abs(nMotorEncoder[motorA]) > 0 && abs(nMotorEncoder[motorB]) > 0) // while motors havent reached initial position
      {}

      if(abs(nMotorEncoder[motorA]) > 0) //checking if motorA has reached inital position
      {
            motor[motorB] = 0;
            while(abs(nMotorEncoder[motorA]) > 0) // while motor havent reached initial position
            {}
            motor[motorA] = 0;

      }
      else if (abs(nMotorEncoder[motorB]) > 0)//checking if motorB has reached inital position
      {
            motor[motorA] = 0;
            while(abs(nMotorEncoder[motorB]) > 0) // while motor havent reached initial position
            {}
            motor[motorB] = 0;
      }
      else
      {
            motor[motorA] = motor[motorB] = 0; // sets faucet motors to 0;
      }
}

}
