#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "dadoskbmStarbucks.h"
#include <fstream>
#include <string>

#define SHOW_TIMES

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HW04App::setup()
{
	vector<Entry*> entries = vector<Entry*>();
	fstream in = fstream("..\\resources\\Starbucks_2006.csv", fstream::in );
	if(!in.is_open())
	{
		console() << "Error opening file" << endl;
		exit(1);
	}
	while(in.good())
	{
		string line;
		getline(in, line);
		//Find locations of the commas
		int comma1 = line.find(',');
		int comma2 = line.find(',', comma1 + 1);
		if(comma1 == line.npos || comma2 == line.npos)
		{
			console() << "Error: Malformed file, line " << entries.size() << endl;
			exit(2);
		}
		string str1 = line.substr(0,comma1 - 1),
			str2 = line.substr(comma1, comma2 - comma1 - 1),
			str3 = line.substr(comma2);
		console() << line << endl;
		Entry* e = new Entry;
		e->identifier = str1;
		e->x = atof(str2.c_str());
		e->y = atof(str2.c_str());
		entries.push_back(e);
	}
	/*for(unsigned int i = 0; i < entries.size(); i++)
	{
		console() << entries[i]->identifier << ", " 
			<< entries[i]->x << ", " << entries[i]->y << endl;
	}*/
	

}

void HW04App::mouseDown( MouseEvent event )
{
}

void HW04App::update()
{
}

void HW04App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04App, RendererGl )
