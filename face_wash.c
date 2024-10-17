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
