#include "dadoskbmStarbucks.h"
#include <vector>
#include <cmath>

using namespace std;

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
	return sqrt((item.x - x) * (item.x - x) + (item.y­ - y) * (item.y - y));
}

/**
* Calculates the distance between this node and the given node.
*/
double Node::distance(Node* node) {return 0.0};

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
	for(int i = 0; i < n; i++)
	{
		placeX(new Node(c[i]), root);
		placeY(new Node(c[i]), root);
	}
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
	vector<Node*> items = vector<Node*>();
	for(Node* cur = root; cur != NULL;)
	{
		items.push_back(cur);
		if(x < cur->item.x)
			cur = cur->leftX;
		else
			cur = cur->rightX;
	}
	Node* closestX;
	while(!items.empty())
	{
		Node* cur = items.back();
		items.pop_back();
		if(cur->distance(x,y) < closestX->distance(x,y))
			closestX = cur;
	}

	//Now same for Y:
	vector<Node*> items = vector<Node*>();
	for(Node* cur = root; cur != NULL;)
	{
		items.push_back(cur);
		if(y < cur->item.y)
			cur = cur->leftY;
		else
			cur = cur->rightY;
	}
	Node* closestY;
	while(!items.empty())
	{
		Node* cur = items.back();
		items.pop_back();
		if(cur->distance(x,y) < closestX->distance(x,y))
			closestX = cur;
	}

	if(closestX->distance(x,y) < closestY->distance(x.y))
		return &closestX->item;
	else
		return &closestY->item;

}


//Returns the nearest Entry in the X-tree
Entry* searchX(double x, Node* parent, Node* closest = NULL)
{
	if(parent == NULL)
		return NULL;
	

}
//Returns the nearest Entry in the Y-tree
Entry* searchY(double y, Node* parent, Node* closest = NULL)
{

}
//Private, recursive method that places the given node in its proper position in the X-tree.

void placeX(Node* toPlace, Node* parent) 
{
	if(parent == NULL)
		parent = toPlace;
	else if(toPlace->item.x < parent->item.x)
	{
		if(parent->leftX == NULL)
			parent->leftX = toPlace;
		else
			placeX(toPlace, parent->leftX);
	}
	else
	{
		if(parent->rightX == NULL)
			parent->rightX = toPlace;
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
			parent->leftY = toPlace;
		else
			placeY(toPlace, parent->leftY);
	}
	else
	{
		if(parent->rightY == NULL)
			parent->rightY = toPlace;
		else
			placeY(toPlace, parent->rightY);
	}
}