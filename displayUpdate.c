void displayUpdate(string mode, float temp_p, int time)
{
	const int WIDTH = 177;
	const int HEIGHT = 127;
	const int ORIGIN = 1;
	string name;

	eraseDisplay();

	// full page rectangle
	drawRect(ORIGIN, HEIGHT, WIDTH, ORIGIN);

	// line between
	drawLine((WIDTH/2)-10, HEIGHT, (WIDTH/2)-10, ORIGIN); // vertical
	drawLine(ORIGIN, HEIGHT/2, (WIDTH/2)-10, HEIGHT/2); // horizontal

	// brush teeth text
	displayBigStringAt(7, HEIGHT-10, "Brush");
	displayBigStringAt(7, HEIGHT-40, "Teeth");

	// face wash text
	displayBigStringAt(12, ORIGIN+20, "Face");
	displayBigStringAt(12, ORIGIN+50, "Wash");

	// temp bar
	drawRect(WIDTH-20, HEIGHT-23, WIDTH-10, ORIGIN+25);
	fillRect(WIDTH-20, (ORIGIN+25) + 77*(temp_p/100.0), WIDTH-10, ORIGIN+25);

	// temp percent display
	displayStringAt(WIDTH-20, ORIGIN+15, "%d%c", temp_p, '%');

	// countdown display
	displayBigStringAt(WIDTH/2+10, HEIGHT/2, "%d%c", time, 's');

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
