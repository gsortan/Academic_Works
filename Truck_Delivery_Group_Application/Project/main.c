#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "DataStructures.h"
#include "mapping.h"
#include "funcs.h"


int main(void)
{
	const struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route greenRoute = getGreenRoute();

	struct Truck tList[3];
	tList[0].curSpace = 0;
	tList[0].curWeight = 0;
	tList[0].distOfShortestPath = 0;
	tList[1].curSpace = 0;
	tList[1].curWeight = 0;
	tList[1].distOfShortestPath = 0;
	tList[2].curSpace = 0;
	tList[2].curWeight = 0;
	tList[2].distOfShortestPath = 0;

	tList[0].path = getBlueRoute();
	tList[1].path = getGreenRoute();
	tList[2].path = getYellowRoute();

	struct Shipment test;
	test.weight = 1;

	printf("=================\n");
	printf("Seneca Deliveries\n");
	printf("=================\n");

	while (test.weight != -1)
	{
		if (test.weight != -1)
		{
			test = read(baseMap, NO_DEBUG, NULL);
		}

		if (test.weight != -1)
		{
			int foundIndex = findBestTruckForShipment(baseMap, tList, test);
			if (foundIndex != -1)
			{
				printResults(tList[foundIndex]);
				loadTruck(&tList[foundIndex], &test);
			}
			else
			{
				printf("No trucks can take the package!\n");
			}
		}
	}

	printf("Thanks for shipping with Seneca!\n");

	return 0;
}