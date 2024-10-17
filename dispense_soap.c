void dispense_soap()
{
	const int STARTPOS = 0;
	const int ENDPOS = 150;

	nMotorEncoder[motorC] = 0;
	motor[motorC] = 25;


	while (nMotorEncoder[motorC] < ENDPOS) {
		if (nMotorEncoder[motorC] >= ENDPOS) {
			motor[motorC] = 0;
		}
		wait1Msec(10);
	}

	wait1Msec(50);

	motor[motorC] = -10;


	while (nMotorEncoder[motorC] > STARTPOS) {
		if (nMotorEncoder[motorC] <= STARTPOS) {
			motor[motorC] = 0;
		}
		wait1Msec(10);
	}

	motor[motorC] = 0;
}
