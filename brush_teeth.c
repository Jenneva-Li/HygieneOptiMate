void brush_teeth(float *Temp_p)
{
	int mode_index = 0;
	for(int i = 0; i < MAX_TIME_ROW; i++)
	{
		if(Mode[i] == "brush_teeth")
		{
			mode_index = i;
			i = 2;
		}
	}
	time1[T2] = 0;
	int time_index = 0;
	while(time_index < 3) //3 time intervals for brush teeth
	{
		float input_time=0;
		update_handles(Temp_p[mode_index]);
		string mode = "brush_teeth";
		time1[T2] = 0;
		float time = time1[T2];//array is in seconds
		while(time <=  Time_intervals[mode_index][time_index])
		{
			input_time = Time_intervals[mode_index][time_index]-time;
			displayUpdate(mode, Temp_p[mode_index], input_time/1000);
			wait1Msec(1000);
			time = time1[T2];
		};
		++time_index;
		water_off();
		if(time_index< 3)
		{
			time1[T2] = 0;
			time = time1[T2];
			while(time <= Time_intervals[mode_index][time_index])
			{
				input_time = Time_intervals[mode_index][time_index]-time;
				displayUpdate(mode, Temp_p[mode_index], input_time/1000);
				wait1Msec(1000);
				time = time1[T2];
			};
			time_index++;
			update_handles(Temp_p[mode_index]);
		}
		if(time_index< 3)
		{
			time1[T2] = 0;
			time = time1[T2];
			while(time <= Time_intervals[mode_index][time_index])
			{
				input_time = Time_intervals[mode_index][time_index]-time;
				displayUpdate(mode, Temp_p[mode_index], input_time/1000);
				wait1Msec(1000);
				time = time1[T2];
			}
			++time_index;
			water_off();
		}
		if(time_index< 3)
		{
			time1[T2] = 0;
			time = time1[T2];
			while(time <= Time_intervals[mode_index][time_index])
			{
				input_time = Time_intervals[mode_index][time_index]-time;
				displayUpdate(mode, Temp_p[mode_index], input_time/1000);
				wait1Msec(1000);
				time = time1[T2];
			}
			time_index++;
		}
	}
}
