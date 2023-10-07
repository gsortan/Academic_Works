#define _CRT_SECURE_NO_WARNINGS
#include "funcs.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>


void clearInputBuffer() {
	char c;
	while ((c = getchar()) != '\n');
}

void loadTruck(struct Truck* t, struct Shipment* s)
{
	if (!isTruckFull(*t, *s))
	{
		t->curSpace += s->size;
		t->curWeight += s->weight;
	}
}

int convLetter(char letterCord)
{
	int convertedLetterNum = letterCord - 'A';

	return convertedLetterNum;
}

struct Shipment read(struct Map m, int debugMode, const char * filePath)
{
	double weight = -1.0f;
	double boxSize = -1.0f;
	int destFlag = 0;
	int numCoord = 0;
	char letter = ' ';
	char destination[200];
	destination[0] = 'A';
	destination[1] = '\0';
	char leftO = ' ';
	int checkInput = 0;
	struct Point destPoint = { 0,0 };
	int invalidMsg = 0;

	int checkWeight = 0;
	int checkSize = 0;
	int checkDest = 0;
	FILE* fptr = NULL;
	if (debugMode == DEBUG)
	{
		fptr = fopen(filePath, "r");
	}

	/*Strict format for the user input must match exactly
	with double space double space integer char coordinates*/
	while (checkInput != 1) //Checkinput!=1 condition
	{
		memset(destination, 0, sizeof(destination));
		//printf("Enter shipment weight, box size and destination (0 0 x to stop):\n");
		if (debugMode)
		{
			printf("Enter shipment weight, box size and destination (0 0 x to stop):\n");
			
				fgets(destination, sizeof(destination), fptr);//stdin
				printf("%s", destination);
			
		}
		else
		{
			printf("Enter shipment weight, box size and destination (0 0 x to stop):\n");
			fgets(destination, sizeof(destination), stdin);

		}

		if (strcmp(destination, "") != 0)
		{

			if (strcmp(destination, "0 0 x\n") == 0)
			{
				checkInput = 1;
				weight = -1.0f;
			}

			if (checkInput == 0)
			{

				int numOfItems = sscanf(destination, " %lf%lf%d%c%c", &weight, &boxSize, &numCoord, &letter, &leftO);

				if (numOfItems != 5 && leftO == '\n' || numOfItems < 5)
				{
					printf("Invalid format for input, try again!\n");
					if (destination[199] != '\n' && strlen(destination) == 199)
					{
						clearInputBuffer();
					}
				}
				else if (leftO != '\n')
				{
					printf("Invalid format for input, try again!\n");
				}
				else
				{
					//The valditation process for every user input

					checkWeight = validWeight(weight);

					if (checkWeight == 0)
					{
						printf("Invalid weight (must be 1-1000 Kg.)\n");
					}

					if (checkWeight == 1)
					{
						checkSize = validSize(boxSize);
					}

					if (checkSize == 0 && checkWeight == 1)
					{
						printf("Invalid size\n");
					}

					if (checkSize == 1)
					{
						//Conversion of letter to number using ascii code
						int convertedLetterNum = letter - 'A';
						numCoord -= 1;
						destPoint.row = numCoord;
						destPoint.col = convertedLetterNum;
						if (isupper(letter))
						{

							checkDest = validDestination(m, destPoint);
						}
						else
						{
							checkDest = 0;
						}

					}


					if (checkDest == 0 && checkWeight == 1 && checkSize == 1)
					{
						printf("Invalid destination\n");
					}

					if (checkDest == 1 && checkWeight == 1 && checkSize == 1)
					{
						checkInput = 1;
					}


				}

			}
		}
	}

	if (debugMode == DEBUG)
	{
		fclose(fptr);
	}
	struct Shipment s;
	s.weight = weight;
	s.size = boxSize;
	s.destination = destPoint;

	return s;
}

int validWeight(double weight)
{
	int wFlag = 0;

	if (weight >= MIN_WEIGHT && weight <= MAX_WEIGHT)
	{
		wFlag = 1;
	}
	return wFlag;
}

int validSize(double size)
{
	double boxSizes[] = { 0.25,0.5,1.0 }; //The box size limits
	int sizeFlag = 0;

	for (int i = 0; i < 3; i++)
	{
		if (size == boxSizes[i])
		{
			sizeFlag = 1;
		}
	}
	return sizeFlag;
}

int validDestination(struct Map m, struct Point p)
{
	int foundPoint = 0;
	int cRow = p.row - 0;
	int cCol = p.col - 0;
	//The map is a 25 x 25 grid so it should stay within those boundaries before
	//attempting to check if the square is on a building for a delivery
	if (cRow < 25 && cRow >= 0 && cCol < 25 && cCol >= 0)
	{
		if (m.squares[cRow][cCol] == 1)
		{
			foundPoint = 1;
		}
	}

	return foundPoint;
}

int isTruckFull(struct Truck truck, struct Shipment box)
{
	int truckFlag = 1;
	double tempVol = truck.curSpace + box.size;
	double tempWeight = truck.curWeight + box.weight;

	if (tempVol <= MAX_CAPACITY && tempWeight <= MAX_WEIGHT)
	{
		truckFlag = 0;
	}
	return truckFlag;
}

double calcShortPathDist(struct Route shortP)
{
	return shortP.numPoints;
}


void determineDivergencePath(struct Truck* truck)
{
	int j = 0;
	int counter = 0;
	int foundPoint = 0;

	truck->divergence_path.routeSymbol = DIVERSION;
	truck->divergence_path.numPoints = 0;

	while (counter != truck->s_Path.numPoints)
	{
		foundPoint = 0;
		for (j = 0; j < truck->path.numPoints; j++)
		{
			if (eqPt(truck->path.points[j], truck->s_Path.points[counter]))
			{
				j = truck->path.numPoints;
				foundPoint = 1;
			}
		}
		if (foundPoint == 0)
		{
			addPointToRoute(&truck->divergence_path, truck->s_Path.points[counter].row,
				truck->s_Path.points[counter].col);
		}
		counter++;
	}
}

void printPath(struct Route path)
{
	int i = 0;

	for (i = 0; i < path.numPoints; i++)
	{
		if (i != path.numPoints)
		{
			printf("%d%c, ", path.points[i].row + 1, path.points[i].col + 'A');
		}
	}
}

int setValidDefaultMinTruck(struct Truck truckList[], struct Shipment package)
{
	int counter = 0;
	int min = 0;
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (truckList[counter].s_Path.numPoints != 0 && !isTruckFull(truckList[counter], package)
			|| truckList[counter].s_Path.numPoints == 0
			&& truckList[counter].exactMatch && !isTruckFull(truckList[counter], package))
		{
			i = 3;
		}
		else
		{
			counter++;
		}
	}

	if (counter == 3)
	{
		counter = -1;
	}

	return counter;
}

double capPercentage(struct Truck t)
{
	double volumePercent = t.curSpace / MAX_CAPACITY;
	double weightPercent = t.curWeight / MAX_WEIGHT;

	return weightPercent + volumePercent;
}

struct Point returnTouchingSquare(struct Map m, struct Point startPoint, struct Point destP)
{
	char up, down, left, right;
	up = destP.col + 1;
	down = destP.col - 1;
	left = destP.row - 1;
	right = destP.row + 1;

	struct Point adjacentPoints[4];
	struct Route adjacentRoute;
	adjacentRoute.numPoints = 0;

	int touchingPoints = 0;

	if (up < MAP_COLS)
	{
		if (m.squares[destP.row][up] == 0)
		{
			touchingPoints++;
			addPointToRoute(&adjacentRoute, destP.row, up);
		}
	}

	if (down > 0)
	{
		if (m.squares[destP.row][down] == 0)
		{
			touchingPoints++;
			addPointToRoute(&adjacentRoute, destP.row, down);
		}
	}

	if (left > 0)
	{
		if (m.squares[left][destP.col] == 0)
		{
			touchingPoints++;
			addPointToRoute(&adjacentRoute, left, destP.col);
		}
	}

	if (right < MAP_ROWS)
	{
		if (m.squares[right][destP.col] == 0)
		{
			touchingPoints++;
			addPointToRoute(&adjacentRoute, right, destP.col);
		}
	}

	struct Point PointReturned; 

	//return a valid point if it satisfies this condition
	if (touchingPoints !=0)
	{
		PointReturned = adjacentRoute.points[getClosestPoint(&adjacentRoute, startPoint)];
	}
	else
	{
		//Invalid square safety check as it is surrounded by building squares
		PointReturned.row = -1;
		PointReturned.col = -1;
	}
	return PointReturned;
}



int  calculateShortestPathIndex(struct Map m, struct Truck* truck, struct Point dest)
{
	double distances[100];
	double minDist = 0;
	int shortestInd = 0;

	for (int i = 0; i < truck->path.numPoints; i++)
	{
		distances[i] = calcShortPathDist(shortestPath(&m, truck->path.points[i], dest));


		if (eqPt(dest, truck->path.points[i]))
		{
			truck->exactMatch = 1;
		}
	}

	minDist = distances[0];
	for (int i = 0; i < truck->path.numPoints; i++)
	{
		if (distances[i] < minDist && distances[i] != 0)
		{
			minDist = distances[i];
			shortestInd = i;
		}
	}

	return shortestInd;
}

int findBestTruckForShipment(struct Map m, struct Truck truckList[], struct Shipment package)
{
	int selectedTruckIndex = -1;
	int closestPtIndex = 0;

	struct Map buildingEdgMap = extractBuildingEdges(m);


	double minDist = 0;
	double minTotalCap = 0;
	double minCap = 0;

	int minIndex = 0;
	struct Point realDest;
	double minDistance = 0;

	int i = 0;
	for (i = 0; i < NUM_TRUCKS; i++)
	{
		truckList[i].exactMatch = 0;
		truckList[i].finalDestination = package.destination;


		if (checkBuildingSquares(m, package.destination) == 4)
		{
			int closePoint = getClosestPoint(&truckList[i].path, package.destination);

			realDest = getClosestEdgePoint(buildingEdgMap, package.destination, truckList[i].path.points[closePoint]);
			truckList[i].finalDestination = realDest;
		}
		else
		{
			int closePIndex = getClosestPoint(&truckList[i].path, package.destination);
			realDest = returnTouchingSquare(m, truckList[i].path.points[closePIndex], package.destination);
		}

		int pt = calculateShortestPathIndex(m, &truckList[i], realDest);
		truckList[i].start.row = truckList[i].path.points[pt].row;
		truckList[i].start.col = truckList[i].path.points[pt].col;

		if (!truckList[i].exactMatch)
		{
			truckList[i].s_Path = shortestPath(&m, truckList[i].path.points[pt], realDest);
		}
		else
		{
			truckList[i].s_Path.numPoints = 0;
		}

		if (truckList[i].s_Path.numPoints > 0 && !truckList[i].exactMatch)
		{
			determineDivergencePath(&truckList[i]);
		}
	}

	for (i = 0; i < NUM_TRUCKS; i++)
	{
		truckList[i].distOfShortestPath = calcShortPathDist(truckList[i].s_Path);
	}

	minIndex = setValidDefaultMinTruck(truckList, package);

	minDist = truckList[minIndex].distOfShortestPath;

	minCap = capPercentage(truckList[minIndex]);


	if (minIndex != -1)
	{
		selectedTruckIndex = minIndex;
		for (i = minIndex; i < NUM_TRUCKS; i++)
		{
			if (truckList[i].s_Path.numPoints != 0 && truckList[i].distOfShortestPath < minDist
				&& !isTruckFull(truckList[i], package) ||
				truckList[i].s_Path.numPoints == 0 && truckList[i].exactMatch
				&& truckList[i].distOfShortestPath < minDist
				&& !isTruckFull(truckList[i], package))
			{
				minDist = truckList[i].distOfShortestPath;
				selectedTruckIndex = i;
			}
			else if (truckList[i].s_Path.numPoints != 0 && truckList[i].distOfShortestPath == minDist
				&& !isTruckFull(truckList[i], package) && capPercentage(truckList[i]) < minCap
				|| truckList[i].s_Path.numPoints == 0 && truckList[i].exactMatch
				&& truckList[i].distOfShortestPath == minDist
				&& !isTruckFull(truckList[i], package) && capPercentage(truckList[i]) < minCap)
			{
				minCap = capPercentage(truckList[i]);
				selectedTruckIndex = i;

			}
		}
	}

	return selectedTruckIndex;
}

void printResults(struct Truck truck)
{

	if (truck.path.routeSymbol == GREEN)
	{
		printf("Ship on GREEN LINE, ");

		if (truck.divergence_path.numPoints != 0 && !truck.exactMatch)
		{
			
			printf("divert:");
			printf("%d%c, ", truck.start.row + 1, truck.start.col + 'A');
			printPath(truck.divergence_path);
			printf("%d%c\n", truck.finalDestination.row + 1, truck.finalDestination.col + 'A');
		}
		else
		{
			printf("No diversion\n");
		}

	}
	else if (truck.path.routeSymbol == BLUE)
	{
		printf("Ship on BLUE LINE, ");

		if (truck.divergence_path.numPoints != 0 && !truck.exactMatch)
		{
			
			printf("divert:");
			printf("%d%c, ", truck.start.row + 1, truck.start.col + 'A');
			printPath(truck.divergence_path);
			printf("%d%c\n", truck.finalDestination.row + 1, truck.finalDestination.col + 'A');
		}
		else
		{
			printf("No diversion\n");
		}
	}

	else if (truck.path.routeSymbol == YELLOW)
	{
		printf("Ship on YELLOW LINE, ");

		if (truck.divergence_path.numPoints != 0 && !truck.exactMatch)
		{
			
			printf("divert:");
			printf("%d%c, ", truck.start.row + 1, truck.start.col + 'A');
			printPath(truck.divergence_path);
			printf("%d%c\n", truck.finalDestination.row + 1, truck.finalDestination.col + 'A');
		}
		else
		{
			printf("No diversion\n");
		}
	}

}


int checkBuildingSquares(struct Map m, struct Point destP)
{
	char up, down, left, right;
	up = destP.col + 1;
	down = destP.col - 1;
	left = destP.row - 1;
	right = destP.row + 1;

	int touch = 0;

	if (up < MAP_COLS)
	{
		if (m.squares[destP.row][up] == 1)
		{
			touch++;
		}
	}

	if (down > 0)
	{
		if (m.squares[destP.row][down] == 1)
		{
			touch++;
		}
	}

	if (left > 0)
	{
		if (m.squares[left][destP.col] == 1)
		{
			touch++;
		}
	}

	if (right < MAP_ROWS)
	{
		if (m.squares[right][destP.col] == 1)
		{
			touch++;
		}
	}
	return touch;
}

struct Point getClosestEdgePoint(struct Map m, struct Point dest, struct Point start)
{
	int row, col;
	double minDistance = 9999;
	double curDist = 0;
	struct Point minPoint = { 0,0 };
	struct Route addedEdgePoints;
	addedEdgePoints.numPoints = 0;
	struct Point lastPoint = { 0,0 };
	double minCheck = 9999;

	for (row = 0; row < 25; row++)
	{
		for (col = 0; col < 25; col++)
		{
			if (m.squares[row][col] == 1)
			{
				struct Point check = { row,col };
				curDist = distance(&dest, &check);
				double checkDist = distance(&start, &check);
				curDist += checkDist;
				if (curDist < minDistance)
				{
					minDistance = curDist;
					minPoint.row = row;
					minPoint.col = col;
					lastPoint = check;
				}

			}
		}
	}

	return minPoint;
}

/// <summary>
/// Calculates a map that extracts all the building edges and only consists of that
/// to calculate the closest edge point in case user picks in the middle of a building
/// </summary>
/// <param name="mapToExtract">The base map to extract from</param>
/// <returns>Returns a map structure that is just building edges</returns>
struct Map extractBuildingEdges(struct Map mapToExtract)
{
	int row, col;
	struct Route edgeSquares;
	edgeSquares.numPoints = 0;
	struct Map totalMap;

	for (row = 0; row < 25; row++)
	{
		for (col = 0; col < 25; col++)
		{
			if (mapToExtract.squares[row][col] == 0)
			{
				struct Point check = { row,col };
				if (checkBuildingSquares(mapToExtract, check) > 0)
				{
					totalMap.squares[row][col] = 1;
				}
				else
				{
					totalMap.squares[row][col] = 0;
				}
			}
			else
			{
				totalMap.squares[row][col] = 0;
			}
		}
	}
	return totalMap;
}

int fileRouteParse(const char* fileName, struct Route checkingRoute)
{
	int row = 0, col = 0;
	int match = 0;
	char fileInput[200];
	FILE* fptr;
	struct Route temp;
	temp.numPoints = 0;
	fptr = fopen(fileName, "r");
	while (fgets(fileInput, sizeof(fileInput), fptr))
	{
		if (sscanf(fileInput, " %d%c", &row, &col) == 2)
		{
			addPointToRoute(&temp, row - 1, col - 'A' + 1);
		}
	}

	for (int i = 0; i < checkingRoute.numPoints; i++)
	{
		if (eqPt(checkingRoute.points[i], temp.points[i]))
		{
			match = 1;
		}
		else
		{
			i = checkingRoute.numPoints;
		}
	}
	return match;

}