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
