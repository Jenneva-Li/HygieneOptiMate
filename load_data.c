void LoadData(TFileHandle fin, float *Temp_p, int num_time)
{
	for(int index=0; index<2; index++)
	{
		readTextPC(fin, Mode[index]);
		int temp_value = 0;
		readIntPC(fin, temp_value);
		Temp_p[index]=temp_value;
		readIntPC(fin, num_time);
		for(int time_index=0; time_index<num_time; time_index++)
		{
			readFloatPC(fin, Time_intervals[index][time_index]);
		}
	}
}
