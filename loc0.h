#ifndef LOC0_H
#define LOC0_H
#include <SFML\Graphics.hpp>
#include <iostream>
#define SIZE_OF_BLOCK 64
#define COUNT_OF_SHIPS 10
using namespace sf;


int WhicShipPresed(Vector2f& MouseMovePos, int startLocateX[], int startLocateY[],
		int shipOrientation[], int sizeShip[]);

void StartWindowAndShips(RenderWindow& MainWindow, Texture& tShips,
		Texture& tLine, int startLocateX[], int startLocateY[],
		int shipOrientation[], int sizeShip[], int firstPicselInTexture[]);
		
void BotleWindow(RenderWindow& MainWindow, Texture& tView,
		Texture& tLine, int viewFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int viewSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS]);

void setPlacemantOfShip(RenderWindow& MainWindow, Texture& tShips,
		Texture& tLine, int Position[COUNT_OF_SHIPS][COUNT_OF_SHIPS]);

void resetLocate(int LocateX[], int LocateY[], int Orientation[]);

bool isLocateGood(int LocateX[], int LocateY[], int Orientation[], int shipSize[],
		int Ans[COUNT_OF_SHIPS][COUNT_OF_SHIPS]);

bool isClearAround(int Ans[COUNT_OF_SHIPS][COUNT_OF_SHIPS], int x, int y, int i);

void PresBatel(int viewFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int viewSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS], 
		int shipLocateFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS], 
		int shipLocateSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS], 
		Vector2i MouseLocate, int& Who);

void AroundDot(int view[COUNT_OF_SHIPS][COUNT_OF_SHIPS]);

#endif // !LOC0_H
