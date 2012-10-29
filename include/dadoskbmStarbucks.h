/**
 * My implementation of the Starbucks class, which utilizes two binary search trees, one for the
 * X-coordinate and one for the Y-coordinate.
 *
 * Copied from design document:
 * Uses 2 binary search trees: One indexed by the X-coordinate, and one by the Y-coordinate.
 * Each Node class will then have four child nodes: two for each tree (i.e. leftX, rightX, 
 * leftY, rightY), and the Starbucks class will still only have one root node as the root for
 * each separate tree will be the same. Items will be placed in the order they appear on the list.
 * Since it is sorted alphabetically by location, the coordinates will be reasonably random.
 *
 * @author Brandon Dadosky
 */
#include "Starbucks.h"
#pragma once


 /*
 * Node class
 */
class Node
{
public:
	Entry item;
	Node* leftX;
	Node* leftY;
	Node* rightX;
	Node* rightY;


	/**
	 * Creates a node for a given item and initializes the child nodes to NULL
	 */
	Node(Entry item);

	/**
	 * Calculates the distance between this node and the given points.
	 */
	double distance(double& x,double& y);

	/**
	 * Calculates the distance between this node and the given node.
	 */
	double distance(Node* node);

};

class dadoskbmStarbucks : public Starbucks
{
public:

	/**
	 * Constructor.
	 */
	dadoskbmStarbucks();

	/**
	 * Creates a node for each entry and places it in the proper position in each
	 * binary search tree. NOTE: some locations are listed twice, duplicates must
	 * be checked for. Duplicates are two entries where |x1 - x2| <= 0.00001 and |y1 - y2| < 0.00001
	 * @param c Array of entries to be built into a tree
	 * @param n Length of c, in number of entries
	 */
	virtual void build(Entry* c,int n);
	
	/**
	 * Searches through both trees, returning the closest found Starbucks location
	 * to the given coordinates
	 * @param x X-coordinate to look at
	 * @param y Y-coordinate to look at
	 * @return Closest entry
	 */
	virtual Entry* getNearest(double x,double y);

private:
	//Root node. Due to the way tree placement is designed, this can be used for both X and Y trees.
	Node* root;

};
