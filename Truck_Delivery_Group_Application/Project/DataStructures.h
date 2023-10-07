//Header file for all neccessary data structures for testing

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define MAX_CAPACITY 36.0 //This is the upper limit for the total number of boxes on a truck
#define MAX_WEIGHT 1000.0 //Max weight for a shipment
#define MIN_WEIGHT 1 //This is the minimum weight for a shipment
#define NUM_TRUCKS 3

#include "mapping.h"


struct Shipment
{
	double weight; //Weight in kg for every shipment 
	double size; //Size of the box
	struct Point destination; //The delivery destination 
};

struct Truck
{
	struct Route path; //This is the actual truck route
	struct Route s_Path; //This is the shortest path from the point on the route that is closest to delivery
	//List that stores the eucld distance calculated for every point on the route 
	double distance[MAX_ROUTE];
	double curSpace; //How much room is inside the truck
	double curWeight;//How much is the weight of the truck
	struct Route divergence_path; //Stores the diverted path from the route
	double distOfShortestPath;
	int exactMatch; 
	struct Point start;
	struct Point finalDestination;
};





#endif





