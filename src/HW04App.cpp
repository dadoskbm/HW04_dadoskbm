#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "dadoskbmStarbucks.h"
#include <fstream>
#include <string>


using namespace ci;
using namespace ci::app;
using namespace std;

class HW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	Starbucks* starbucks;
};

void HW04App::setup()
{
	vector<Entry> entries = vector<Entry>();
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
		e->y = atof(str2.c_str());
		entries.push_back(*e);
	}
	
	//Vector of entries is built, convert to array and call dadoskbmStarbucks.build()

	Entry* arr = new Entry[entries.size()];
	for(unsigned int i = 0; i < entries.size(); i++)
		arr[i] = entries[i];

	starbucks = new dadoskbmStarbucks();
	starbucks->build(arr, entries.size());

	/*double x, y;
	console() << "Enter in X-coordinate: ";
	cin >> x;
	console() << endl;
	console() << "Enter in Y-coordinate: ";
	cin >> y;
	console() << endl;*/

	Entry* entry = starbucks->getNearest(0.103189049,0.4057225);
		
	console() << "Your nearest Starbucks:" << endl
		<< entry->identifier << endl << entry->x << endl << entry->y;

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
