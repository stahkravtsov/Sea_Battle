#include <SFML\Graphics.hpp>
#include <iostream>
#include "loc0.h"
#define SIZE_OF_BLOCK 64
#define COUNT_OF_SHIPS 10
using namespace sf;


int main() {

		int iWindowWight = 24 * SIZE_OF_BLOCK, iWindowHight = 16 * SIZE_OF_BLOCK;

		RenderWindow app(VideoMode(iWindowWight, iWindowHight), "My window");

		Texture t;
		t.loadFromFile("shipsMinimalism.png");

		Texture tLine;
		tLine.loadFromFile("line.png");
		
		Texture tView;
		tView.loadFromFile("view.png");

		Sprite s(tView);
		float fSizeBloc = SIZE_OF_BLOCK;
		int shipLocateFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
				shipLocateSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS];

		int viewFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS] = {},
				viewSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS] = {};

		setPlacemantOfShip(app, t, tLine, shipLocateFirst);
		setPlacemantOfShip(app, t, tLine, shipLocateSecond);
		int Who = 1;

		while(app.isOpen()) {
				Vector2i MouseLocate = Mouse::getPosition(app);
				
				Event event;
				app.clear(Color(255, 255, 255, 255));
				while(app.pollEvent(event)) {

						if(event.type == Event::Closed) {
								app.close();
						}
						 
						if(event.type == Event::MouseButtonPressed) {
								if(event.key.code == Mouse::Left) {
										PresBatel(viewFirst, viewSecond, shipLocateFirst, shipLocateSecond, MouseLocate, Who);
								}
						}


				}

				BotleWindow(app, tView, tLine, viewFirst, viewSecond);

		}
}


