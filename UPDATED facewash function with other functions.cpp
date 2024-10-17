//motor A and B for faucet
//A is hot and B is cold
//motor C for soap

const int MAX_TIME_COL=3;
const int MAX_TIME_ROW=2;
const int FACEWASH_TIMES = 3; // time intervals number for face wash, 
//this number must be odd and greater than or equal to 1 
float Time_intervals[MAX_TIME_ROW][MAX_TIME_COL]=
{
	{5000, 10000, 15000}, // 5 10, 15
	{10000, 120000, 15000}
};

string Mode[MAX_TIME_ROW] =
{
	"face_washing", "teeth_brushing"
};

void water_off();
void update_handles(int temp_p);
void face_wash(int *Temp_p);
void displayUpdate(string mode, int temp_p, int time);

task main()
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;
	int Temp_p[MAX_TIME_ROW]={75, 25};


	face_wash(Temp_p);
}
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

void update_handles(int temp_p)
{
	int hot_encoder = 0;
	int cold_encoder = 0;

	if(temp_p >= 50)
	{
		hot_encoder = -170;
		cold_encoder = ((100.0 - temp_p)/50.0)*-170.0;
	}
	else
	{
		cold_encoder = -170;
		hot_encoder = (temp_p/50.0)*-170.0;
	}

	setMotorTarget(motorA, hot_encoder, 10);
	setMotorTarget(motorB, cold_encoder, 10);

	waitUntilMotorStop(motorB);
	waitUntilMotorStop(motorA);
}

void displayUpdate(string mode, int temp_p, int time)
{
	const int WIDTH = 177;
	const int HEIGHT = 127;
	const int ORIGIN = 1;
	string name;

	eraseDisplay();

	// full page rectangle
	drawRect(ORIGIN, HEIGHT, WIDTH, ORIGIN);

	// line between
	drawLine((WIDTH/2)-10, HEIGHT, (WIDTH/2)-10, ORIGIN); // vert
	drawLine(ORIGIN, HEIGHT/2, (WIDTH/2)-10, HEIGHT/2); // horiz

	// brush teeth text
	displayBigStringAt(7, HEIGHT-10, "Brush");
	displayBigStringAt(7, HEIGHT-40, "Teeth");

	// face wash text
	displayBigStringAt(12, ORIGIN+20, "Face");
	displayBigStringAt(12, ORIGIN+50, "Wash");

	// temp bar
	drawRect(WIDTH-20, HEIGHT-23, WIDTH-10, ORIGIN+25);
	fillRect(WIDTH-20, (ORIGIN+25) + 75*(temp_p/100.0), WIDTH-10, ORIGIN+25);

	// temp percent display
	displayStringAt(WIDTH-20, ORIGIN+15, "%d%c", temp_p, '%');

	// countdown display
	displayBigStringAt(WIDTH/2+10, HEIGHT/2, "%d %c", time, 's');

	if (mode == "brush_teeth")
	{
		name = "brushing teeth";
		// pressed
		displayInverseBigStringAt(7, HEIGHT-10, "Brush");
		displayInverseBigStringAt(7, HEIGHT-40, "Teeth");

		//unpressed
		displayBigStringAt(12, ORIGIN+20, "Face");
		displayBigStringAt(12, ORIGIN+50, "Wash");
	}

	else if (mode == "wash_face")
	{
		name = "washing face";
		// pressed
		displayInverseBigStringAt(12, ORIGIN+20, "Face");
		displayInverseBigStringAt(12, ORIGIN+50, "Wash");

		// unpressed
		displayBigStringAt(7, HEIGHT-10, "Brush");
		displayBigStringAt(7, HEIGHT-40, "Teeth");
	}
	else
	{
		name = "hand washing";
		// unpressed
		//brush
		displayBigStringAt(7, HEIGHT-10, "Brush");
		displayBigStringAt(7, HEIGHT-40, "Teeth");
		//face
		displayBigStringAt(12, ORIGIN+20, "Face");
		displayBigStringAt(12, ORIGIN+50, "Wash");
	}

	// mode name display
	displayStringAt(WIDTH/2, HEIGHT-10, name);

	if (time == 0)
	{
		drawBmpfile(0, 0, "smile");
	}
}

void face_wash(int *Temp_p) //for Robotc 1d arrays are treated exactly the same as c++ but the way they are recieved is different
{	int mode_index = 0;
	for(int i = 0; i < MAX_TIME_ROW; i++)
	{
		if(Mode[i] == "face_washing")
		{
			mode_index = i;
			i = 2;
		}
	}

	time1[T2] = 0;
	int time_index = 0;

	while(time_index < FACEWASH_TIMES) 
	{
		float input_time = 0;
		update_handles(Temp_p[mode_index]);
		string mode = "wash_face";
		time1[T2] = 0;
		float time = time1[T2];
		while(time <=  Time_intervals[mode_index][time_index])
		{
			input_time = Time_intervals[mode_index][time_index] - time;
			displayUpdate(mode, Temp_p[mode_index], input_time/1000); // time casts itself as a int, input time is divided by 100 because its in ms
			wait1Msec(1000);
			time = time1[T2];
		};
		++time_index;
		water_off();
		if(time_index  < FACEWASH_TIMES)
		{
			time1[T2] = 0;
			time = time1[T2];
			while(time <= 	Time_intervals[mode_index][time_index])
			{
				input_time = Time_intervals[mode_index][time_index] - time;
				displayUpdate(mode, Temp_p[mode_index], input_time/1000);
				wait1Msec(1000);
				time = time1[T2];
			}
			time_index++;
		}
	}

}
