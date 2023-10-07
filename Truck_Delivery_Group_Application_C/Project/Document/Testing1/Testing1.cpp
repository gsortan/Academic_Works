//SFT211_NEE Group 1
//MILESTONE 3 blackbox test

#include "pch.h"
#include "CppUnitTest.h"
#include "funcs_r.h"
#include "map_r.h"
#include "DataStructures.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing1
{
	TEST_CLASS(blackboxtest)
	{
		struct Map m = populateMap();
	public:
		//Test TB01 
		TEST_METHOD(TB01_01)
		{
			int result = validWeight(1.0);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB01_02)
		{
			int result = validWeight(500);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB01_03)
		{
			int result = validWeight(1000);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB01_04)
		{
			int result = validWeight(0);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB01_05)
		{
			int result = validWeight(1000.5);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB01_06)
		{
			int result = validWeight(-1);
			Assert::AreEqual(0, result);
		}

		// Test TB02
		TEST_METHOD(TB02_01)
		{
			int result = validSize(0.25);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB02_02)
		{
			int result = validSize(0.5);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB02_03)
		{
			int result = validSize(1);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB02_04)
		{
			int result = validSize(0);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB02_05)
		{
			int result = validSize(2);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB02_06)
		{
			int result = validSize(-0.25);
			Assert::AreEqual(0, result);
		}

		//Duplicate with whitebox test
		TEST_METHOD(TB02_07)
		{
			int result = validSize(0.125);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB02_08)
		{
			int result = validSize(0.75);
			Assert::AreEqual(0, result);
		}

		//Test TB03
		TEST_METHOD(TB03_01)
		{
			struct Point p = { 1, 1 }; //2B
			
			int result = validDestination(m, p);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB03_02)
		{
			struct Point p = { 11,11 }; //12L
			int result = validDestination(m, p);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB03_03)
		{
			struct Point p = { 23,24 }; //24Y
			int result = validDestination(m, p);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB03_04)
		{
			struct Point p = {0,convLetter('X')}; //X
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_05)
		{
			struct Point p = { 25,1 }; //26B
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_06)
		{
			struct Point p = { -2,1 }; //-1B
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_07)
		{
			struct Point p = { 0,25 }; //1Z
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_08)
		{
			struct Point p = { 9, convLetter('X')}; //10
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_09)
		{
			struct Point p = { 9, 12 }; //10M
			int result = validDestination(m,p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_10)
		{
			struct Point p = { 23,24 }; //24Y
			int result = validDestination(m, p);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB03_11)
		{
			struct Point p = { 0,11 }; //1
			int result = validDestination(m, p);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB03_12)
		{
			struct Point p = { 23,24 }; //24Y
			int result = validDestination(m, p);
			Assert::AreEqual(1, result);
		}

		//Test TB04
		TEST_METHOD(TB04_01)
		{
			struct Truck truck; //truck already full
			truck.curWeight = 1000;
			truck.curSpace = 36;
			struct Shipment box; //very small box
			box.weight = 0.1;
			box.size = 0.25;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB04_02)
		{
			struct Truck truck; //empty truck
			truck.curWeight = 0;
			truck.curSpace = 35.5;
			struct Shipment box; 
			box.weight = 1000.0;
			box.size = 0.5;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB04_03)
		{
			struct Truck truck; //half max weight truck
			truck.curWeight = 500.0;
			truck.curSpace = 35.75;
			struct Shipment box; 
			box.weight = 500.1;
			box.size = 1.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TB04_04)
		{
			struct Truck truck; //half max space truck
			truck.curWeight = 100.0;
			truck.curSpace = 36.0;
			struct Shipment box; 
			box.weight = 1.0;
			box.size = 0.5;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(1, result);
		}

		//Test TB05
		TEST_METHOD(TB05_01)
		{
			struct Route shortP;
			shortP.numPoints = 0; //set num of points to zero first or else garbage values
			//Adds points and need more than one point to calculate the distance
			addPointToRoute(&shortP, 0, 0);
			addPointToRoute(&shortP, 0, 2);
			double result = calcShortPathDist(shortP);
			Assert::AreEqual(2.0, result, 0.00000001); //double threshhold tolerance for 3rd param
		}

		TEST_METHOD(TB05_02)
		{
			struct Route shortP;
			shortP.numPoints = 0; 
			addPointToRoute(&shortP, 0, 0);
			addPointToRoute(&shortP, 0, 6);
			double result = calcShortPathDist(shortP);
			Assert::AreEqual(2.0, result, 0.00000001); //double threshhold tolerance for 3rd param
		}

		//Test TB06
		TEST_METHOD(TB06_01)
		{
			char letterCord = 'A';
			int result = convLetter(letterCord);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TB06_02)
		{
			char letterCord = 'Z';
			int result = convLetter(letterCord);
			Assert::AreEqual(25, result);
		}


        TEST_METHOD(TB08_01)
		{
			struct Truck truckList[1];
			truckList[0].s_Path.numPoints = 0;

			determineDivergencePath(truckList);

			Assert::AreEqual(0, truckList[0].s_Path.numPoints);
		}
		
		TEST_METHOD(TB09_01)
		{
			struct Truck t;
			t.curSpace = 0;
			t.curWeight = 0;
			struct Shipment s;
			s.weight = 500;
			s.size = 0.25;

			loadTruck(&t, &s);
			Assert::AreEqual(0.25,t.curSpace,0.0000001);
			Assert::AreEqual(500, t.curWeight, 0.0000001);
		}

		
	};

	//Test TB11
	TEST_CLASS(blackboxTB11)
	{
		//Test TB11 
		
		TEST_METHOD(TB11_01)
		{
			Truck t;
			t.curWeight = 500;
			t.curSpace = 18;
			double result = capPercentage(t);
			Assert::AreEqual(1.0, result, 0.000001);
		}
	};


	TEST_CLASS(whiteboxtest)
	{
	public:

		TEST_METHOD(TW01_01)
		{
			int result = validSize(0.125);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TW01_02)
		{
			int result = validSize(0.75);
			Assert::AreEqual(0, result);
		}

		//TW04
		TEST_METHOD(TW04_01)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 0.0;
			truck.curSpace = 0.0;
			box.weight = 500.0;
			box.size = 18.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TW04_02)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 0.0;
			truck.curSpace = 0.0;
			box.weight = 1000.0;
			box.size = 36.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TW04_03)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 0.0;
			truck.curSpace = 0.0;
			box.weight = 2000.0;
			box.size = 18.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TW04_04)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 0.0;
			truck.curSpace = 0.0;
			box.weight = 500.0;
			box.size = 50.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(1, result);
		}

		TEST_METHOD(TW04_05)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 500.0;
			truck.curSpace = 18.0;
			box.weight = 100.0;
			box.size = 10.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TW04_06)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 500.0;
			truck.curSpace = 18.0;
			box.weight = 500.0;
			box.size = 18.0;
			int result = isTruckFull(truck, box);
			Assert::AreEqual(0, result);
		}

		//TW05
		TEST_METHOD(TW05_01)
		{
			struct Route shortP;
			shortP.numPoints = 4;
			shortP.points[0] = { 0,0 };
			shortP.points[1] = { 1,0 };
			shortP.points[2] = { 2,0 };
			shortP.points[3] = { 3,0 };
			double result = calcShortPathDist(shortP);
			Assert::AreEqual(4.0, result);
		}

		TEST_METHOD(TW05_02)
		{
			struct Route shortP;
			shortP.numPoints = 2;
			shortP.points[0] = { 0,0 };
			shortP.points[1] = { 1,0 };
			shortP.points[2] = { 2,0 };
			shortP.points[3] = { 3,0 };
			double result = calcShortPathDist(shortP);
			Assert::AreEqual(2.0, result);
		}

		//Test TW06
		TEST_METHOD(TW06_01)
		{
			char letterCord = 'A';
			int result = convLetter(letterCord);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TW06_02)
		{
			char letterCord = 'Z';
			int result = convLetter(letterCord);
			Assert::AreEqual(25, result);
		}
		

	};

	TEST_CLASS(integrationTesting)
	{
	public:
		struct Map m = populateMap();
		
		

		//isTruckFull + loadTruck
		TEST_METHOD(TI01_01)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 500.0;
			truck.curSpace = 18.0;
			box.weight = 100.0;
			box.size = 10.0;
			int result = isTruckFull(truck, box);
					
			if (result == 0)
			{
				loadTruck(&truck, &box);
				Assert::AreEqual(600, truck.curWeight, 0.0000001);
				Assert::AreEqual(28, truck.curSpace, 0.0000001);
			}
			else {
				Assert::AreEqual(0, result);
			}
		}

		TEST_METHOD(TI01_02)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 0;
			truck.curSpace = 0;
			box.weight = 1000.0;
			box.size = 36;
			int result = isTruckFull(truck, box);

			if (result == 0)
			{
				loadTruck(&truck, &box);
				Assert::AreEqual(1000, truck.curWeight, 0.0000001);
				Assert::AreEqual(36, truck.curSpace, 0.0000001);
			}
			else {
				Assert::AreEqual(0, result);
			}
		}

		TEST_METHOD(TI01_03)
		{
			struct Truck truck;
			struct Shipment box;
			truck.curWeight = 800;
			truck.curSpace = 10;
			box.weight = 200;
			box.size = 10;
			int result = isTruckFull(truck, box);

			

			if (result == 0)
			{
				loadTruck(&truck, &box);
				Assert::AreEqual(1000, truck.curWeight, 0.0000001);
				Assert::AreEqual(20, truck.curSpace, 0.0000001);
			}
			else {
				Assert::AreEqual(0, result);
			}
		}
		
		//extractBuildingEdges + getClosestEdgePoint
		TEST_METHOD(TI02_01) {//Basic Scenario
			struct Point dest = { 12,5 };
			struct Point start = { 0,0 };
			struct Point expectedClosestEdgePoint = { 12,5 };
			struct Map extractedEdgeMap = extractBuildingEdges(m);
			struct Point closestEdgePoint = getClosestEdgePoint(extractedEdgeMap, dest, start);

			Assert::AreEqual(expectedClosestEdgePoint.row, closestEdgePoint.row);
			Assert::AreEqual(expectedClosestEdgePoint.col, closestEdgePoint.col);
		}

		TEST_METHOD(TI02_02) {//No Building Edges
			struct Point dest = { 18,18 };
			struct Point start = { 5,5 };
			struct Point expectedClosestEdgePoint = { 5,5 };
			struct Map extractedEdgeMap = extractBuildingEdges(m);
			struct Point closestEdgePoint = getClosestEdgePoint(extractedEdgeMap, dest, start);

			Assert::AreEqual(expectedClosestEdgePoint.row, closestEdgePoint.row);
			Assert::AreEqual(expectedClosestEdgePoint.col, closestEdgePoint.col);
		}

		TEST_METHOD(TI02_03) {//Multiple Closest Edge Points
			struct Point dest = { 7,22 };
			struct Point start = { 8,22 };
			struct Point expectedClosestEdgePoint = { 7,21 };
			struct Map extractedEdgeMap = extractBuildingEdges(m);
			struct Point closestEdgePoint = getClosestEdgePoint(extractedEdgeMap, dest, start);

			Assert::AreEqual(expectedClosestEdgePoint.row, closestEdgePoint.row);
			Assert::AreEqual(expectedClosestEdgePoint.col, closestEdgePoint.col);
		}

		TEST_METHOD(TI03_01)
		{
			struct Shipment shipment = read(m, 1, "userinput.txt");
			Assert::IsTrue(shipment.weight != -1.0);
		}

		TEST_METHOD(TI03_02)
		{
			struct Shipment shipment = read(m, 1, "userinput2.txt");
			Assert::IsTrue(shipment.weight == -1.0);
		}
		TEST_METHOD(TI04_01)
		{
			struct Point start = { 0, 0 };
			struct Point dest = { 9, 2 };
			Route testShort = shortestPath(&m, start, dest);

			Assert::IsTrue(testShort.numPoints > 0);
		}

		TEST_METHOD(TI04_02)
		{
			struct Point start = { 2, convLetter('A') };
			struct Point dest = { 6, convLetter('Y') };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);
		}

		TEST_METHOD(TI04_03)
		{
			struct Point start = { 6, convLetter('V') };
			struct Point dest = { 7, convLetter('Y') };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);
		}


		TEST_METHOD(TI05_01)
		{
			struct Truck truck;
			truck.path = getYellowRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 9, 4 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);


			truck.s_Path.numPoints = 0;

			determineDivergencePath(&truck);

			Assert::AreEqual(0, truck.s_Path.numPoints);
		}

		TEST_METHOD(TI05_02)
		{
			struct Truck truck;
			truck.path = getYellowRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 13, 3 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);

			truck.s_Path.numPoints = 2;

			determineDivergencePath(&truck);

			Assert::AreEqual(2, truck.s_Path.numPoints);
		}

		TEST_METHOD(TI05_03)
		{
			struct Truck truck;
			truck.path = getBlueRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 9, 10 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);

			truck.s_Path.numPoints = 0;

			determineDivergencePath(&truck);

			Assert::AreEqual(0, truck.s_Path.numPoints);
		}

		TEST_METHOD(TI05_04)
		{
			struct Truck truck;
			truck.path = getBlueRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 13, 18 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);

			truck.s_Path.numPoints = 7;

			determineDivergencePath(&truck);

			Assert::AreEqual(7, truck.s_Path.numPoints);
		}

		TEST_METHOD(TI05_05)
		{
			struct Truck truck;
			truck.path = getGreenRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 2, 20 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);

			truck.s_Path.numPoints = 0;

			determineDivergencePath(&truck);

			Assert::AreEqual(0, truck.s_Path.numPoints);
		}

		TEST_METHOD(TI05_06)
		{
			struct Truck truck;
			truck.path = getGreenRoute();

			struct Point start = { 0, 0 };
			struct Point dest = { 15, 22 };

			Route testShort = shortestPath(&m, start, dest);
			Assert::IsTrue(testShort.numPoints > 0);

			truck.s_Path.numPoints = 7;

			determineDivergencePath(&truck);

			Assert::AreEqual(7, truck.s_Path.numPoints);
		}

		//Test for one touching point
		TEST_METHOD(TI06_01) {
			// Obstacle squares, start Point: (0, 0), destination Point: (7, 24)
			struct Point start = { 0, 0 };
			struct Point dest = { 7, 24 };
			
			// Use returnTouchingSquare to find the nearest adjacent square
			struct Point touchingSquare = returnTouchingSquare(m, start, dest);

			struct Point adjacentTest = { 6,24 };
			Assert::IsTrue(eqPt(touchingSquare, adjacentTest));
		}


		//Test for two touching points
		TEST_METHOD(TI06_02) {
			// Mixed squares, start Point: (0, 0), destination Point: (6, 7)
			struct Point start = { 0, 0 };
			struct Point dest = { 6, 7};
		
			// Use returnTouchingSquare to find the nearest adjacent square
			struct Point touchingSquare = returnTouchingSquare(m, start, dest);

			struct Point closest = { 6,6 };
			// Verify that closest reachable Point to start is returned (Closest Point: (6, 6))
			Assert::IsTrue(eqPt(closest,touchingSquare));
		}

		//Test 3 touching points
		TEST_METHOD(TI06_03) {
			//start Point: (0, 0), destination Point: (2, 12)
			struct Point start = { 0, 0 };
			struct Point dest = { 2, convLetter('M') };

			// Use returnTouchingSquare to find the nearest adjacent square
			struct Point touchingSquare = returnTouchingSquare(m, start, dest);

			struct Point adjacentTest = { 2,11 };
			Assert::IsTrue(eqPt(touchingSquare, adjacentTest));

		}

		//Test for 4 touching points
		TEST_METHOD(TI06_04) {
			//start Point: (0, 0), destination Point: (2, 10)
			struct Point start = { 0, 0 };
			struct Point dest = { 2, convLetter('K') };

			// Use returnTouchingSquare to find the nearest adjacent square
			struct Point touchingSquare = returnTouchingSquare(m, start, dest);

			struct Point adjacentTest = { 2,9 };
			Assert::IsTrue(eqPt(touchingSquare, adjacentTest));

		}


		//Testing if the square is completely blocked off and surrounded by buildings
		//on all sides, hence returns -1 values for x and y for the point returned
		TEST_METHOD(TI06_05) {
			// test square surrounded by buildings, start Point: (0, 0), destination Point: (14, 13)
			struct Point start = { 0, 0 };
			struct Point dest = { 14, convLetter('N')};

			// Use returnTouchingSquare to find the nearest adjacent square
			struct Point touchingSquare = returnTouchingSquare(m, start, dest);

			// Verify that it's an invalid square
			struct Point testPoint = { -1, -1 };
			Assert::IsTrue(eqPt(touchingSquare,testPoint));
		}


		

		


		TEST_METHOD(TI07_01) {
			struct Map m = populateMap();
			struct Truck truck;
			struct Point pathPoints[] = {
				{0, 0},
				{1, 1},
				{2, 2}
			};
			truck.path.numPoints = sizeof(pathPoints) / sizeof(pathPoints[0]);
			for (int i = 0; i < truck.path.numPoints; i++) {
				truck.path.points[i] = pathPoints[i];
			}
			struct Point destination = {3, 3};
			int shortestPathIndex = calculateShortestPathIndex(m, &truck, destination);
			int expectedShortestPathIndex = 2;
			Assert::AreEqual(expectedShortestPathIndex, shortestPathIndex);
		}
		
		TEST_METHOD(TI07_02) {
			struct Map m = populateMap();
			struct Truck truck;
			struct Point pathPoints[] = {
				{0, 0},
				{1, 1},
				{2, 2}
			};
			truck.path = getGreenRoute();
			struct Point destination = {0, 24};
			int shortestPathIndex = calculateShortestPathIndex(m, &truck, destination);
			int expectedShortestPathIndex = 27;
			Assert::AreEqual(expectedShortestPathIndex, shortestPathIndex);
		}
		
		TEST_METHOD(TI07_03) {
			struct Map m = populateMap();
			struct Truck truck;
			truck.path.numPoints = 0;
			struct Point destination = {12, 12};
			int shortestPathIndex = calculateShortestPathIndex(m, &truck, destination);
			int expectedShortestPathIndex = 0;
			Assert::AreEqual(expectedShortestPathIndex, shortestPathIndex);
		}
		
		TEST_METHOD(TI08_01) {
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
			struct Shipment package = { 100, 0.5, {6,24} };
			
			Assert::AreEqual(findBestTruckForShipment(m, tList, package), 1);
		}
		
		TEST_METHOD(TI08_02) {			
			struct Truck tList[3];
			tList[0].curSpace = 0;
			tList[0].curWeight = 0;
			tList[0].distOfShortestPath = 0;
			tList[1].curSpace = 0;
			tList[1].curWeight = 1000;
			tList[1].distOfShortestPath = 0;
			tList[2].curSpace = 0;
			tList[2].curWeight = 0;
			tList[2].distOfShortestPath = 0;
			
			tList[0].path = getBlueRoute();
			tList[1].path = getGreenRoute();
			tList[2].path = getYellowRoute();
			struct Shipment package = { 100, 0.5, {6,24} };
			
			Assert::AreEqual(findBestTruckForShipment(m, tList, package), 0);
		}
		
		TEST_METHOD(TI08_03) {			
			struct Truck tList[3];
			tList[0].curSpace = 0;
			tList[0].curWeight = 1000;
			tList[0].distOfShortestPath = 0;
			tList[1].curSpace = 0;
			tList[1].curWeight = 1000;
			tList[1].distOfShortestPath = 0;
			tList[2].curSpace = 0;
			tList[2].curWeight = 1000;
			tList[2].distOfShortestPath = 0;
			
			tList[0].path = getBlueRoute();
			tList[1].path = getGreenRoute();
			tList[2].path = getYellowRoute();
			struct Shipment package = { 100, 0.5, {6,24} };
			
			Assert::AreEqual(findBestTruckForShipment(m, tList, package), -1);
		}

	
	};

	TEST_CLASS(acceptanceTesting)
	{
	public:
		Map m = populateMap();
		struct Truck tList[3];
		int index = 0;
		int match = 0;

		acceptanceTesting()
		{	
			tList[0].curSpace = 0;
			tList[0].curWeight = 0;
			tList[0].distOfShortestPath = 0;
			tList[1].curSpace = 0;
			tList[1].curWeight = 0;
			tList[1].distOfShortestPath = 0;
			tList[2].curSpace = 0;
			tList[2].curWeight = 0;
			tList[2].distOfShortestPath = 0;
			tList[0].divergence_path.numPoints = 0;
			tList[1].divergence_path.numPoints = 0;
			tList[2].divergence_path.numPoints = 0;

			tList[0].path = getBlueRoute();
			tList[1].path = getGreenRoute();
			tList[2].path = getYellowRoute();
		}

	

		TEST_METHOD(TA01_01)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			Assert::AreEqual(package.destination.row + 1, 12);
			Assert::AreEqual(package.destination.col - 0, convLetter('L'));
			Assert::AreEqual(package.size, 0.5);
			Assert::AreEqual(package.weight, 20.0);
		}

		TEST_METHOD(TA01_02)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, 0);
			Assert::AreEqual(tList[index].divergence_path.numPoints, 0);
		}

		TEST_METHOD(TA01_03)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);
			package = read(m, DEBUG, "acceptance2.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, 1);
			match = fileRouteParse("greenRouteAcceptance.txt", tList[index].divergence_path);
			Assert::AreEqual(match, 1);
		}

		TEST_METHOD(TA01_04)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance2.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance3.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, 1);
			match = fileRouteParse("greenRouteAcceptance.txt", tList[index].divergence_path);
			Assert::AreEqual(match, 1);
		}

		TEST_METHOD(TA01_05)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance2.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance3.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance3.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, 0);
			match = fileRouteParse("blueRouteAcceptance.txt", tList[index].divergence_path);
			Assert::AreEqual(match, 0);
		}

		TEST_METHOD(TA01_06)
		{
			struct Shipment package = read(m, DEBUG, "acceptance1.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance2.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance3.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "acceptance3.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);
			
			package = read(m, DEBUG, "exitCondition.txt");
			Assert::AreEqual(package.weight, -1.0);
		}

		//All trucks are full test for the user with repeated inputs, can't load anymore
		TEST_METHOD(TA01_07)
		{
			struct Shipment package = read(m, DEBUG, "fullTruckInput.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "fullTruckInput.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "fullTruckInput.txt");
			index = findBestTruckForShipment(m, tList, package);
			loadTruck(&tList[index], &package);

			package = read(m, DEBUG, "fullTruckInput.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, -1);
		}

		//If a square is picked that is in the middle of a building for the destination 
		//and it's not an edge
		TEST_METHOD(TA01_08)
		{
			struct Shipment package = read(m, DEBUG, "buildingMiddleInput.txt");
			index = findBestTruckForShipment(m, tList, package);
			Assert::AreEqual(index, 0);
			Assert::AreEqual(tList[index].divergence_path.numPoints, 0);
		}
	};
}


//TEST_METHOD(TW08_01)
		//{
		//	// Test for no divergence points
		//	struct Truck truck;
		//	truck.s_Path.numPoints = 5;
		//	truck.s_Path.points[0] = Point(0, 0);
		//	truck.s_Path.points[1] = Point(0, 1);
		//	truck.s_Path.points[2] = Point(0, 2);
		//	truck.s_Path.points[3] = Point(0, 3);
		//	truck.s_Path.points[4] = Point(0, 4);

		//	determineDivergencePath(truck);

		//	Assert::AreEqual(0, truck.divergence_path.numPoints);
		//}

		//TEST_METHOD(TW08_02)
		//{
		//	// Test for one divergence point
		//	struct Truck truck;
		//	truck.s_Path.numPoints = 5;
		//	truck.s_Path.points[0] = Point(0, 0);
		//	truck.s_Path.points[1] = Point(0, 1);
		//	truck.s_Path.points[2] = Point(0, 2); // Divergence point
		//	truck.s_Path.points[3] = Point(0, 3);
		//	truck.s_Path.points[4] = Point(0, 4);

		//	determineDivergencePath(truck);

		//	Assert::AreEqual(1, truck.divergence_path.numPoints);
		//	Assert::AreEqual(Point(0, 2), truck.divergence_path.points[0]);
		//}

		//TEST_METHOD(TW08_03)
		//{
		//	// Test for multiple divergence points
		//	struct Truck truck;
		//	truck.s_Path.numPoints = 5;
		//	truck.s_Path.points[0] = Point(0, 0);
		//	truck.s_Path.points[1] = Point(0, 1); // Divergence point
		//	truck.s_Path.points[2] = Point(0, 2); // Divergence point
		//	truck.s_Path.points[3] = Point(0, 3);
		//	truck.s_Path.points[4] = Point(0, 4);

		//	determineDivergencePath(truck);

		//	Assert::AreEqual(2, truck.divergence_path.numPoints);
		//	Assert::AreEqual(Point(0, 1), truck.divergence_path.points[0]);
		//	Assert::AreEqual(Point(0, 2), truck.divergence_path.points[1]);
		//}


		//TEST_METHOD(TW09_01)
		//{
		//	// Test for all invalid trucks
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 0;
		//	truckList[1].s_Path.numPoints = 0;
		//	truckList[2].s_Path.numPoints = 0;

		//	int result = setValidDefaultMinTruck(truckList, 3);

		//	Assert::AreEqual(-1, result);
		//}

		//TEST_METHOD(TW09_02)
		//{
		//	// Test for one valid truck
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 0; // Invalid
		//	truckList[1].s_Path.numPoints = 6; // Valid
		//	truckList[2].s_Path.numPoints = 0; // Invalid

		//	int result = setValidDefaultMinTruck(truckList, 3);

		//	Assert::AreEqual(1, result);
		//}

		//TEST_METHOD(TW09_03)
		//{
		//	// Test for multiple valid trucks
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 0; // Invalid
		//	truckList[1].s_Path.numPoints = 8; // Valid
		//	truckList[2].s_Path.numPoints = 12; // Valid

		//	int result = setValidDefaultMinTruck(truckList, 3);

		//	Assert::AreEqual(1, result);
		//}



		//TEST_METHOD(TW10_01)
		//{
		//	// Test for all invalid trucks
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 0;
		//	truckList[1].s_Path.numPoints = 0;
		//	truckList[2].s_Path.numPoints = 0;

		//	struct Shipment package;
		//	package.destination = Point(5, 5); // Any valid destination
		//	package.weight = 100; // Any valid weight
		//	package.size = 0.5; // Any valid size

		//	int result = findBestTruckForShipment(truckList, 3, package);

		//	Assert::AreEqual(-1, result);
		//}

		//TEST_METHOD(TW10_02)
		//{
		//	// Test for one valid truck
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 0; // Invalid
		//	truckList[1].s_Path.numPoints = 6; // Valid
		//	truckList[2].s_Path.numPoints = 0; // Invalid

		//	struct Shipment package;
		//	package.destination = Point(3, 3); // Any valid destination
		//	package.weight = 500; // Any valid weight
		//	package.size = 0.25; // Any valid size

		//	int result = findBestTruckForShipment(truckList, 3, package);

		//	Assert::AreEqual(1, result);
		//}

		//TEST_METHOD(TW10_03)
		//{
		//	// Test for multiple valid trucks with different capacities
		//	struct Truck truckList[3];
		//	truckList[0].s_Path.numPoints = 8; // Valid
		//	truckList[1].s_Path.numPoints = 10; // Valid
		//	truckList[2].s_Path.numPoints = 12; // Valid

		//	struct Shipment package;
		//	package.destination = Point(8, 8); // Any valid destination
		//	package.weight = 800; // Any valid weight
		//	package.size = 0.5; // Any valid size

		//	int result = findBestTruckForShipment(truckList, 3, package);

		//	Assert::AreEqual(0, result);
		//}