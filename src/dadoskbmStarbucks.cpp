#include "dadoskbmStarbucks.h"
#include <vector>
#include <cmath>
#include "cinder/app/App.h"

using namespace std;


//Private, recursive method that places the given node in its proper position in the X-tree.
void placeX(Node* toPlace, Node* parent) 
{
	
	if(parent == NULL)
		parent = toPlace;
	else if(toPlace->item.x < parent->item.x)
	{
		if(parent->leftX == NULL)
		{
			parent->leftX = toPlace;
		}
		else
			placeX(toPlace, parent->leftX);
	}
	else
	{
		if(parent->rightX == NULL)
		{
			parent->rightX = toPlace;
		}
		else
			placeX(toPlace, parent->rightX);
	}
}
//Same method for Y-tree.
void placeY(Node* toPlace, Node* parent) 
{
	if(parent == NULL)
		parent = toPlace;
	else if(toPlace->item.y < parent->item.y)
	{
		if(parent->leftY == NULL)
		{
			parent->leftY = toPlace;
		}
		else
			placeY(toPlace, parent->leftY);
	}
	else
	{
		if(parent->rightY == NULL)
		{
			parent->rightY = toPlace;
		}
		else
			placeY(toPlace, parent->rightY);
	}
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
	if(n == 0) return; //Don't build an empty list!
#ifdef SHOW_TIMES
	int stepCount = 1;
	int time = clock();
#endif
	//Create the root
	root = new Node(c[0]);
	for(int i = 1; i < n; i++)
	{
		Node* node = new Node(c[i]);
		placeX(node, root);
		placeY(node, root);
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
	vector<Node*> items;
	Node* cur = root;
	do
	{
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
	vector<Node*> items2;
	cur = root; //Reset for Y-tree
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
			closestY = cur;
	}
#ifdef SHOW_TIMES
	int timeTaken = (clock() - time); //Clock increment is 1 ms
	ci::app::console() << "Get Nearest called\nSteps taken(X): " << stepCountX << "\nSteps taken(Y): " << stepCountY << "\nTime taken: " << timeTaken << " ms" << endl;
#endif

	if(closestX->distance(x,y) < closestY->distance(x,y))
		return &closestX->item;
	else
		return &closestY->item;
}