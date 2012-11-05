#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "dadoskbmStarbucks.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include <fstream>

#define WIDTH 764
#define HEIGHT 424
#define MAP_WIDTH 764
#define MAP_HEIGHT 424
#define MAP_OFFSET_X 0
#define MAP_OFFSET_Y 0

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

private:
	dadoskbmStarbucks* starbucks;
	Surface bg, clone;
	Vec2i lastHighlighted;
};

/**
 * Converts data coordinates (from Starbucks.h) to image coordinates
 */
Vec2i coord2Img(const double& x, const double& y);

/**
 * Converts image coordinates to data coordinates (From Starbucks.h)
 */
Vec2f img2Coord(const int& x, const int& y);

void HW04App::setup()
{
	//Initialize random number generator
	srand(time(NULL));

	vector<Entry> entries;
	ifstream in = ifstream("..\\resources\\Starbucks_2006.csv", fstream::in );
	if(!in.is_open())
	{
		console() << "Error opening file" << endl;
		exit(1);
	}
	while(in.good())
	{
		string line;
		getline(in, line, '\r');
		//Find locations of the commas
		int comma1 = line.find(',');
		int comma2 = line.find(',', comma1 + 1);
		if(comma1 == line.npos || comma2 == line.npos)
		{
			console() << "Error: Malformed file, line " << entries.size() << endl;
			exit(2);
		}
		string str1 = line.substr(0,comma1),
			str2 = line.substr(comma1 + 1, comma2 - comma1 - 1),
			str3 = line.substr(comma2 + 1);
		Entry* e = new Entry;
		e->identifier = str1;
		e->x = atof(str2.c_str());
		e->y = atof(str3.c_str());
		entries.push_back(*e);
	}
	
	//Vector of entries is built, convert to array and call dadoskbmStarbucks.build()

	Entry* arr = new Entry[entries.size()];
	for(unsigned int i = 0; i < entries.size(); i++)
		arr[i] = entries[i];

	starbucks = new dadoskbmStarbucks();
	starbucks->build(arr, entries.size());

	/*
	//DEBUG CODE:
	Entry* entry = starbucks->getNearest(0.167744693,0.3479477);
		
	console() << "Your nearest Starbucks:" << endl
		<< entry->identifier << endl << entry->x << endl << entry->y << endl;
	*/

	//DRAWING SETUP
	lastHighlighted = Vec2i(-1, -1);
	bg = loadImage("..\\resources\\usa.jpg");
	clone = bg.clone();
	
	for(unsigned int i = 0; i < entries.size(); i++)
	{
		Entry entry = entries[i];
		Vec2i coords = coord2Img(entry.x, entry.y);
		clone.setPixel(coords, Color8u(0xff,0x00,0x00));
	}
	
}

void HW04App::prepareSettings(Settings* settings)
{
	settings->setResizable(false);
	settings->setWindowSize(WIDTH, HEIGHT);
}

void HW04App::mouseDown( MouseEvent event )
{
	Vec2f coords = img2Coord(event.getX(), event.getY());
	Entry* entry = starbucks->getNearest(coords.x, coords.y);

	Vec2i currentLoc = coord2Img(entry->x, entry->y);

	//Clear last highlighted and set to nearest Starbucks
	if(lastHighlighted.x != -1)
		clone.setPixel(lastHighlighted, Color8u(0xff, 0x00, 0x00));
	lastHighlighted = currentLoc;

	clone.setPixel(currentLoc, Color8u(0xee, 0xc9, 0x00));
	

	console() << "Your nearest Starbucks:" << endl
		<< entry->identifier << endl << entry->x << endl << entry->y << endl;
}

void HW04App::update()
{
}

void HW04App::draw()
{
	gl::draw(gl::Texture(clone));
	gl::drawSolidCircle(lastHighlighted, 4);
}

Vec2i coord2Img(const double& x, const double& y)
{
	return Vec2i(floor(x * MAP_WIDTH) + MAP_OFFSET_X, floor(HEIGHT - (y * HEIGHT)) + MAP_OFFSET_Y);
}

Vec2f img2Coord(const int& x, const int& y)
{
	return Vec2f((double)(x - MAP_OFFSET_X)/(double)WIDTH,(double)((HEIGHT - y) - MAP_OFFSET_Y)/(double)HEIGHT);
}

CINDER_APP_BASIC( HW04App, RendererGl )
