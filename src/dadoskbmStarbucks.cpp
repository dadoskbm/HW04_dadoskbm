#include "dadoskbmStarbucks.h"
#include <vector>
#include <cmath>
#include "cinder/app/App.h"
#ifdef SHOW_TIMES
  #include <ctime>
#endif

using namespace std;


//Private, recursive method that places the given node in its proper position in the X-tree.
Node* placeX(Entry toPlace, Node* parent) 
{
	if(parent == NULL)
		parent = new Node(toPlace);
	else if(parent->item.x == toPlace.x)
		return parent;
	else if(toPlace.x < parent->item.x)
		parent->leftX = placeX(toPlace,parent->leftX);
	else
		parent->rightX = placeX(toPlace, parent->rightX);
	return parent;
}
//Same method for Y-tree.
Node* placeY(Entry toPlace, Node* parent) 
{
	if(parent == NULL)
		parent = new Node(toPlace);
	else if(parent->item.y == toPlace.y)
		return parent;
	else if(toPlace.y < parent->item.y)
		parent->leftY = placeY(toPlace,parent->leftY);
	else
		parent->rightY = placeY(toPlace, parent->rightY);
	return parent;
}
/**
* Creates a node for a given item and initializes the child nodes to NULL
*/
Node::Node(Entry item)
{
	this->item = item;
	this->leftX = NULL;
	this->leftY = NULL;
	this->rightX = NULL;
	this->rightY = NULL;
}

/**
* Calculates the distance between this node and the given points.
*/
double Node::distance(double& x,double& y)
{
	return sqrt((item.x - x) * (item.x - x) + (item.y - y) * (item.y - y));
}

/**
* Calculates the distance between this node and the given node.
*/
double Node::distance(Node* node)
{
	return distance(node->item.x, node->item.y);
}

/**
* Constructor.
*/
dadoskbmStarbucks::dadoskbmStarbucks()
{
	root = NULL;
}
/**
* Creates a node for each entry and places it in the proper position in each
* binary search tree. NOTE: some locations are listed twice, duplicates must
* be checked for. Duplicates are two entries where |x1 - x2| <= 0.00001 and |y1 - y2| < 0.00001
* @param c Array of entries to be built into a tree
* @param n Length of c, in number of entries
*/
void dadoskbmStarbucks::build(Entry* c,int n)
{
#ifdef SHOW_TIMES
	int stepCount = 0;
	int time = clock();
#endif
	for(int i = 0; i < n; i++)
	{
		root = placeX(c[i], root);
		root = placeY(c[i], root);
#ifdef SHOW_TIMES
		stepCount++;
#endif
	}
#ifdef SHOW_TIMES
	int timeTaken = (clock() - time); //Clock increment is 1 ms
	ci::app::console() << "Build called\nSteps taken: " << stepCount << "\nTime taken: " << timeTaken << "ms" << endl;
#endif
}
	
/**
* Searches through both trees, returning the closest found Starbucks location
* to the given coordinates
* @param x X-coordinate to look at
* @param y Y-coordinate to look at
* @return Closest entry
*/
Entry* dadoskbmStarbucks::getNearest(double x,double y)
{
#ifdef SHOW_TIMES
	int stepCountX = 0;
	int stepCountY = 0;
	int time = clock();
#endif
	vector<Node*> items = vector<Node*>();
	Node* cur;
	do
	{
		cur = root;
		items.push_back(cur);
		if(x < cur->item.x)
			cur = cur->leftX;
		else
			cur = cur->rightX;
	
#ifdef SHOW_TIMES
		stepCountX++;
#endif
	} while(cur != NULL);
	Node* closestX = NULL;
	while(!items.empty())
	{
		Node* cur = items.back();
		items.pop_back();
		if(closestX == NULL || cur->distance(x,y) < closestX->distance(x,y))
			closestX = cur;
	}

	//Now same for Y:
	vector<Node*> items2 = vector<Node*>();
	cur = NULL; //Reset for Y-tree
	do
	{
		items2.push_back(cur);
		if(y < cur->item.y)
			cur = cur->leftY;
		else
			cur = cur->rightY;
	
#ifdef SHOW_TIMES
		stepCountY++;
#endif
	} while(cur != NULL);
	Node* closestY = NULL;
	while(!items2.empty())
	{
		Node* cur = items2.back();
		items2.pop_back();
		if(closestY == NULL || cur->distance(x,y) < closestX->distance(x,y))
			closestX = cur;
	}
#ifdef SHOW_TIMES
	int timeTaken = (clock() - time); //Clock increment is 1 ms
	ci::app::console() << "Get Nearest called\nSteps taken(X): " << stepCountX << "\nSteps taken(Y): " << stepCountY << "\nTime taken: " << timeTaken << "ms" << endl;
#endif

	if(closestX->distance(x,y) < closestY->distance(x,y))
		return &closestX->item;
	else
		return &closestY->item;

}