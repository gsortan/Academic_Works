//Functio definitions 

#ifndef FUNCS_H
#define FUNCS_H
#define NO_DEBUG 0
#define DEBUG 1
#include"DataStructures.h"


///<summary>
/// This just clears the input buffer of any dangling new line characters
/// </summary>
/// <returns>Doesn't return anything </returns>
void clearInputBuffer();

///<summary>
/// Utility function to convert a capital letter coordinate into a number
/// using ascii code. For example A = 0, B = 1, C = 2 and so on
/// </summary>
/// <param name="letterCord">- The letter coordinate to convert</param>
/// <returns>Returns converted letter into numeric value </returns>
int convLetter(char letterCord);

///<summary>
/// This loads the shipment onto the truck and updates those capacity 
/// values accordingly 
/// </summary>
/// <param name="t">- The truck being loaded</param>
/// <param name="s">- The shipment being carried</param>
/// <returns>Doesn't return anything, the truck object is changed through the pointer </returns>
void loadTruck(struct Truck* t, struct Shipment* s);

/// <summary>
/// This function is to prompt the user to input the shipment weight, box size and destination.  Also, it  will use functions for validation routines ?int validWeight, int validSize and validDesination to verify the result.  
/// If the validations all pass, a shipment struct is created and returned. 
/// </summary>
/// <param name="m">- The map of the delivery area</param>
/// <returns>Returns a newly created shipment structure using the results of the user input </returns>
struct Shipment read(struct Map m, int debugMode, const char *filePath);

/// <summary>
/// Checks if the weight is within a valid range
/// </summary>
/// <param name="weight">- the weight of a box</param>
/// <returns>Returns integer 1 if weight is between 1 and 1000 inclusive, 0 otherwise if weight isn't valid </returns>
int validWeight(double weight);

/// <summary>
/// Checks if the size is within a valid range
/// </summary>
/// <param name="size">- the size of a box</param>
/// <returns>Returns integer that is 1 if valid size range that is 0.25,0.5,1.0 respectively, 
/// 0 otherwise if it's not any of those</returns>
int validSize(double size);

/// <summary>
/// Checks if the destination from the user is valid for a delivery
/// </summary>
/// <param name="m">- The map of the delivery area</param>
/// <param name="dest">- The destination of the delivery</param>
/// <returns>Returns integer, 1 if it is a valid destination square, 0 otherwise if it isn't valid </returns>
int validDestination(struct Map m, struct Point p);

/// <summary>
/// Checks if the truck can actually carry the shipment by looking at weight and space 
/// and returns a 0 if it’s possible to put on the truck 
/// </summary>
/// <param name="truck">- The truck being checked for curSpace or curWeight</param>
/// <param name="box">- The shipment being checked for size or weight</param>
/// <returns>An integer is returned for determining space or weight. 1 if the box isn't able to put in the 
/// truck and 0 otherwise  </returns>
int isTruckFull(struct Truck truck, struct Shipment box);


/// <summary>
/// This will caculate from point to point on the shortest path 
///  what the total distance is
/// </summary>
/// <param name="shortP">- The shortest route used for this calculation</param>
/// <returns>Returns a double of the caculated shortest path distance</returns>
double calcShortPathDist(struct Route shortP);

/// <summary>
///Calculates the divergence path of truck by comparing the shortest path and the original route. 
/// any points that do not match will be stored as deviance points.  
/// </summary>
/// <param name="truck">- The truck being used to determine divergence path</param>
/// <returns> Does not return anything but the divergence path 
/// is going to be stored in truck pointer’s divergence route variable  </returns>
void determineDivergencePath(struct Truck* truck);

///<summary>
/// Prints out the coordinates of the path
/// </summary>
/// <param name="path">- Route to print</param>
/// <returns>Doesn't return anything </returns>
void printPath(struct Route path);

/// <summary>
///Loops through all trucks in truck array and tries to set a default minimum truck index 
/// for later use when it is comparing shortest distances to weed out any trucks that do 
/// not successfully deliver anything 
/// </summary>
/// <param name="truckList">The list of trucks used to set the minimum default</param>
/// <returns>Will return an integer index value of the first valid default min truck 
/// otherwise returns ? if none of the trucks can reach the destination  </returns>
int setValidDefaultMinTruck(struct Truck truckList[], struct Shipment package);

/// <summary>
///Calculate total percentage of weight and space to decide which truck to load if 
/// they are the same distance from the delivery
/// </summary>
/// <param name="t">The truck being used to calculate the total percentage</param>
/// <returns>Will return the total capacity percentage for comparison purposes </returns>
double capPercentage(struct Truck t);

/// <summary>
/// This will take a truck and calculate what the closest possible point to a delivery is
/// using the shortest path algorithm for every single point on the route then
/// calculating total distance
/// </summary>
/// <param name="m"> The base map of buildings</param>
/// <param name="truck">A truck for the calculation</param>
/// <param name="dest">The final destination for delivery</param>
/// <returns></returns>
int calculateShortestPathIndex(struct Map m, struct Truck* truck, struct Point dest);

/// <summary>
/// This is used for selecting the closest adjacent square from the destination 
/// for delivery that is not an obstacle. Needs to be used to prevent an infinte loop from
/// happening in shortest path algorithm since it cannot use a building square with
/// a 1 in the map.
/// </summary>
/// <param name="m">The basemap</param>
/// <param name="startPoint">The starting point of the truck route</param>
/// <param name="destP">Final delivery building square</param>
/// <returns>A non-obstacle point to be used for shortest path finding</returns>
struct Point returnTouchingSquare(struct Map m, struct Point startPoint, struct Point destP);


///<summary>
/// Takes into consideration the capacity of the truck, shipment size and weight,
///  route of the truck tries to place which is closest to destination. 
/// If no truck can take it, then returns -1 
/// </summary>
/// <param name="m">- Map of delivery space with buildings</param>
/// <param name="truckList">- The list of trucks for delivery</param>
/// <param name="package">- The shipment for delivery</param>
/// <returns>Returns an integer that is the index for the truck that can
/// do the shipment with the shortest path, otherwise return -1 if it can't find any trucks. </returns>
int findBestTruckForShipment(struct Map m, struct Truck truckList[], struct Shipment package);

/// <summary>
/// Prints out the end result for the user if a truck can take a shipment 
/// and which path to take along with diversion path if there is one.
/// </summary>
/// <param name="truck">The selected truck to print out</param>
void printResults(struct Truck truck);

/// <summary>
/// Checks and counts all squares that are buildings that touch this non-building point
/// </summary>
/// <param name="m">The base map for deliveries</param>
/// <param name="destP">The point to check</param>
/// <returns>Returns an integer that defines how many buildings surround the point,
/// return 0 if no buildings are around it</returns>
int checkBuildingSquares(struct Map m, struct Point destP);

/// <summary>
/// Makes a map of calculated building edges 
/// </summary>
/// <param name="mapToExtract">The map to make a building edges map out of</param>
/// <returns>Returns the building edges map</returns>
struct Map extractBuildingEdges(struct Map mapToExtract);

/// <summary>
/// For route comparison purposes, compares every point on path to whatever is 
/// recorded in the text file and returns an integer value that is 1 or 0
/// 1 is a match and 0 isn't
/// </summary>
/// <param name="fileName">File path name for route</param>
/// <param name="checkingRoute">The route being checked against</param>
/// <returns>Returns an integer value</returns>
int fileRouteParse(const char* fileName, struct Route checkingRoute);

/// <summary>
/// Calculates the closest edge point on the map to both the destination and
/// a point on the truck route
/// </summary>
/// <param name="m">This is the base map</param>
/// <param name="dest">The destination point that is inside a building</param>
/// <param name="start">The point that is closest on the truck route</param>
/// <returns>Returns the closest edge point for use as the destination for
/// shortest path algorithm so it doesn't get stuck</returns>
struct Point getClosestEdgePoint(struct Map m, struct Point dest, struct Point start);
#endif