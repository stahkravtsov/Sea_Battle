#include "loc0.h"

//--------------------------------------------------------------------------------
int WhicShipPresed(Vector2f& MouseMovePos, int startLocateX[], int startLocateY[],
		int shipOrientation[], int sizeShip[]) {

		for(int i = 0; i < COUNT_OF_SHIPS; i++) {

				if(MouseMovePos.x >= startLocateX[i] * SIZE_OF_BLOCK &&
						MouseMovePos.x <= startLocateX[i] * SIZE_OF_BLOCK +
						( sizeShip[i] * SIZE_OF_BLOCK - SIZE_OF_BLOCK ) *
						( 1 - shipOrientation[i] ) + SIZE_OF_BLOCK) {

						if(MouseMovePos.y >= startLocateY[i] * SIZE_OF_BLOCK &&
								MouseMovePos.y <= startLocateY[i] * SIZE_OF_BLOCK +
								( sizeShip[i] * SIZE_OF_BLOCK - SIZE_OF_BLOCK ) *
								shipOrientation[i] + SIZE_OF_BLOCK) {
								return  i;
						}
				}

		}
		return -1;
}

//--------------------------------------------------------------------------------
void StartWindowAndShips(RenderWindow& MainWindow, Texture& tShips,
		Texture& tLine, int startLocateX[], int startLocateY[],
		int shipOrientation[], int sizeShip[], int firstPicselInTexture[]) {

		Sprite Ship(tShips);

		Sprite Line(tLine);

		MainWindow.clear(Color(255, 255, 255, 255));

		//Reset
		Line.setTextureRect(IntRect(SIZE_OF_BLOCK, SIZE_OF_BLOCK,
				6 * SIZE_OF_BLOCK, 2 * SIZE_OF_BLOCK));
		Line.setPosition(3 * SIZE_OF_BLOCK, 13 * SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Next
		Line.setTextureRect(IntRect(5 * SIZE_OF_BLOCK, 5 * SIZE_OF_BLOCK,
				6 * SIZE_OF_BLOCK, 2 * SIZE_OF_BLOCK));
		Line.setPosition(14 * SIZE_OF_BLOCK, 13 * SIZE_OF_BLOCK);
		MainWindow.draw(Line);


		//Left
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Right
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(11 * SIZE_OF_BLOCK - 8, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Top
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Down
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK, 11 * SIZE_OF_BLOCK - 8);
		MainWindow.draw(Line);

		for(int i = 0; i < 10; i++) {

				Line.setTextureRect(IntRect(0, 0,
						10 * SIZE_OF_BLOCK, 4));
				Line.setPosition(SIZE_OF_BLOCK, ( 2 + i ) * SIZE_OF_BLOCK - 2);
				MainWindow.draw(Line);
		}

		for(int i = 0; i < 10; i++) {

				Line.setTextureRect(IntRect(0, 0, 4,
						10 * SIZE_OF_BLOCK));
				Line.setPosition(( 2 + i ) * SIZE_OF_BLOCK - 2, SIZE_OF_BLOCK);
				MainWindow.draw(Line);
		}


		//відображення кораблів
		for(int i = 0; i < COUNT_OF_SHIPS; i++) {
				Ship.setTextureRect(IntRect(firstPicselInTexture[i] * SIZE_OF_BLOCK, 0,
						sizeShip[i] * SIZE_OF_BLOCK, SIZE_OF_BLOCK));

				if(shipOrientation[i] == 1) {
						Ship.setRotation(90);
				} else {
						Ship.setRotation(0);
				}

				Ship.setPosition(startLocateX[i] * SIZE_OF_BLOCK +
						( shipOrientation[i] * SIZE_OF_BLOCK ),
						startLocateY[i] * SIZE_OF_BLOCK);
				Ship.setColor(Color(50, 255, 255, 128));

				MainWindow.draw(Ship);
		}
		MainWindow.display();
}

//--------------------------------------------------------------------------------
void setPlacemantOfShip(RenderWindow& MainWindow, Texture& tShips, Texture& tLine,
		int Position[COUNT_OF_SHIPS][COUNT_OF_SHIPS]) {
		Vector2f startOffset(SIZE_OF_BLOCK * 13, SIZE_OF_BLOCK);
		Sprite Ship(tShips);
		int LocateX[COUNT_OF_SHIPS] = { 14, 16, 18, 20, 15, 17, 19, 14, 18, 14 },
				LocateY[COUNT_OF_SHIPS] = { 2, 2, 2, 2, 4, 4, 4, 7, 7, 9 },
				sizeShip[COUNT_OF_SHIPS] = { 1, 1, 1, 1, 2, 2, 2, 3 ,3, 4 },
				firstPicselInTexture[COUNT_OF_SHIPS] = { 0, 0, 0, 0, 1, 1, 1, 3, 3, 6 },
				shipOrientation[COUNT_OF_SHIPS] = { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 };

		while(MainWindow.isOpen()) {

				Vector2f MousePos(Mouse::getPosition(MainWindow));

				Event event;
				while(MainWindow.pollEvent(event)) {
						if(event.type == Event::Closed) {
								MainWindow.close();
						}

						if(event.type == Event::MouseButtonPressed) {
								if(event.key.code == Mouse::Right) {
										//оберт корабля при натисканні правої кнопки миші
										int iNum = WhicShipPresed(MousePos, LocateX,
												LocateY, shipOrientation, sizeShip);
										if(iNum != -1) {

												shipOrientation[iNum] = ( 1 - shipOrientation[iNum] );
										}

								}

								if(event.key.code == Mouse::Left) {
										//reset
										if(MousePos.x >= 3 * SIZE_OF_BLOCK &&
												MousePos.x <= 9 * SIZE_OF_BLOCK &&
												MousePos.y >= 13 * SIZE_OF_BLOCK &&
												MousePos.y <= 15 * SIZE_OF_BLOCK) {
												resetLocate(LocateX, LocateY, shipOrientation);
										}

										//next step
										if(MousePos.x >= 14 * SIZE_OF_BLOCK &&
												MousePos.x <= 20 * SIZE_OF_BLOCK &&
												MousePos.y >= 13 * SIZE_OF_BLOCK &&
												MousePos.y <= 15 * SIZE_OF_BLOCK) {

												if(isLocateGood(LocateX, LocateY, shipOrientation, sizeShip, Position)) {
														MainWindow.clear(Color(0, 0, 0, 255));
														return;
												}
										}


								}
						}

				}

				//пересування кораблів при натиснутій правій кнопці мишки
				int iNumberShip = -1;
				while(Mouse::isButtonPressed(Mouse::Left)) {

						Vector2f MouseMovePos(Mouse::getPosition(MainWindow));

						//визначення корабля, на який натиснули
						if(iNumberShip == -1) {
								iNumberShip = WhicShipPresed(MouseMovePos, LocateX,
										LocateY, shipOrientation, sizeShip);

						}

						if(iNumberShip != -1) {


								int xMove = static_cast<int>( MouseMovePos.x / SIZE_OF_BLOCK ),
										yMove = static_cast<int>( MouseMovePos.y / SIZE_OF_BLOCK );

								LocateX[iNumberShip] = xMove;
								LocateY[iNumberShip] = yMove;
						}

						StartWindowAndShips(MainWindow, tShips,
								tLine, LocateX, LocateY,
								shipOrientation, sizeShip, firstPicselInTexture);

				}

				StartWindowAndShips(MainWindow, tShips,
						tLine, LocateX, LocateY,
						shipOrientation, sizeShip, firstPicselInTexture);
		}
}

//--------------------------------------------------------------------------------
void resetLocate(int LocateX[], int LocateY[], int Orientation[]) {
		int startLocateX[COUNT_OF_SHIPS] = { 14, 16, 18, 20, 15, 17, 19, 14, 18, 14 },
				startLocateY[COUNT_OF_SHIPS] = { 2, 2, 2, 2, 4, 4, 4, 7, 7, 9 },
				shipOrientation[COUNT_OF_SHIPS] = { 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 };
		for(int i = 0; i < COUNT_OF_SHIPS; i++) {
				LocateX[i] = startLocateX[i];
				LocateY[i] = startLocateY[i];
				Orientation[i] = shipOrientation[i];
		}
}

//--------------------------------------------------------------------------------
bool isLocateGood(int LocateX[], int LocateY[], int Orientation[], int shipSize[],
		int Ans[COUNT_OF_SHIPS][COUNT_OF_SHIPS]) {
		for(int i = 0; i < COUNT_OF_SHIPS; i++)
				for(int j = 0; j < COUNT_OF_SHIPS; j++)
						Ans[i][j] = -1;

		for(int i = 0; i < COUNT_OF_SHIPS; i++) {
				//	std::cout << i << " ";
				if(LocateX[i] >= 1 && LocateX[i] <= 10 &&
						LocateY[i] >= 1 && LocateY[i] <= 10) {
						//	std::cout << "First" << std::endl;
						if(LocateX[i] + ( shipSize[i] * ( 1 - Orientation[i] ) - ( 1 - Orientation[i] ) ) >= 1 &&
								LocateX[i] + ( shipSize[i] * ( 1 - Orientation[i] ) - ( 1 - Orientation[i] ) ) <= 10 &&
								LocateY[i] + ( shipSize[i] * Orientation[i] - Orientation[i] ) >= 1 &&
								LocateY[i] + ( shipSize[i] * Orientation[i] - Orientation[i] ) <= 10) {
								//			std::cout << "Second" << std::endl;


								for(int j = LocateX[i]; j <= LocateX[i] +
										( shipSize[i] * ( 1 - Orientation[i] ) -
												( 1 - Orientation[i] ) ); j++) {
										if(Ans[j - 1][LocateY[i] - 1] != -1 && Ans[j - 1][LocateY[i] - 1] != i) {
												return 0;
										} else if(isClearAround(Ans, j - 1, LocateY[i] - 1, i)) {
												Ans[j - 1][LocateY[i] - 1] = i;
												//						std::cout << "Third" << std::endl;

										} else return 0;
								}

								for(int j = LocateY[i]; j <= LocateY[i] +
										( shipSize[i] * ( Orientation[i] ) - ( Orientation[i] ) ); j++) {
										if(Ans[LocateX[i] - 1][j - 1] != -1 && Ans[LocateX[i] - 1][j - 1] != i) {
												return 0;
										} else if(isClearAround(Ans, LocateX[i] - 1, j - 1, i)) {
												Ans[LocateX[i] - 1][j - 1] = i;
												//					std::cout << "Fourth" << std::endl;

										} else return 0;
								}

						} else {
								return 0;
						}

				} else {
						return 0;
				}
		}
}

//--------------------------------------------------------------------------------
bool isClearAround(int Ans[COUNT_OF_SHIPS][COUNT_OF_SHIPS], int x, int y, int i) {
		if(x > 0 && y > 0 && ( Ans[x - 1][y - 1] != -1 && Ans[x - 1][y - 1] != i )) return 0;
		if(y > 0 && ( Ans[x][y - 1] != -1 && Ans[x][y - 1] != i )) return 0;
		if(x < 9 && y > 0 && ( Ans[x + 1][y - 1] != -1 && Ans[x + 1][y - 1] != i )) return 0;
		if(x > 0 && ( Ans[x - 1][y] != -1 && Ans[x - 1][y] != i )) return 0;
		if(x < 9 && ( Ans[x + 1][y] != -1 && Ans[x + 1][y] != i )) return 0;
		if(x > 0 && y < 9 && ( Ans[x - 1][y + 1] != -1 && Ans[x - 1][y + 1] != i )) return 0;
		if(y < 9 && ( Ans[x][y + 1] != -1 && Ans[x][y + 1] != i )) return 0;
		if(x < 9 && y < 9 && ( Ans[x + 1][y + 1] != -1 && Ans[x + 1][y + 1] != i )) return 0;

		return 1;
}

//--------------------------------------------------------------------------------
void BotleWindow(RenderWindow& MainWindow, Texture& tView,
		Texture& tLine, int viewFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int viewSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS]) {


		Sprite Ship(tView);

		Sprite Line(tLine);

		MainWindow.clear(Color(255, 255, 255, 255));

		//Left 1
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Right 1
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(11 * SIZE_OF_BLOCK - 8, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Top 1
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Down 1
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK, 11 * SIZE_OF_BLOCK - 8);
		MainWindow.draw(Line);

		//Left 2
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(13 * SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Right 2
		Line.setTextureRect(IntRect(0, 0,
				8, 10 * SIZE_OF_BLOCK));
		Line.setPosition(11 * SIZE_OF_BLOCK - 8 + 12 * SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Top 2
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK + 12 * SIZE_OF_BLOCK, SIZE_OF_BLOCK);
		MainWindow.draw(Line);

		//Down 2
		Line.setTextureRect(IntRect(0, 0,
				10 * SIZE_OF_BLOCK, 8));
		Line.setPosition(SIZE_OF_BLOCK + 12 * SIZE_OF_BLOCK, 11 * SIZE_OF_BLOCK - 8);
		MainWindow.draw(Line);


		for(int i = 0; i < 10; i++) {

				Line.setTextureRect(IntRect(0, 0,
						10 * SIZE_OF_BLOCK, 4));
				Line.setPosition(SIZE_OF_BLOCK, ( 2 + i ) * SIZE_OF_BLOCK - 2);
				MainWindow.draw(Line);

				Line.setPosition(SIZE_OF_BLOCK + 12 * SIZE_OF_BLOCK, ( 2 + i ) * SIZE_OF_BLOCK - 2);
				MainWindow.draw(Line);

		}

		for(int i = 0; i < 10; i++) {

				Line.setTextureRect(IntRect(0, 0, 4,
						10 * SIZE_OF_BLOCK));
				Line.setPosition(( 2 + i ) * SIZE_OF_BLOCK - 2, SIZE_OF_BLOCK);
				MainWindow.draw(Line);

				Line.setPosition(( 2 + i ) * SIZE_OF_BLOCK - 2 + 12 * SIZE_OF_BLOCK, SIZE_OF_BLOCK);
				MainWindow.draw(Line);
		}

		for(int i = 0; i < COUNT_OF_SHIPS; i++) {
				for(int j = 0; j < COUNT_OF_SHIPS; j++) {
						Ship.setTextureRect(IntRect(viewFirst[i][j] * SIZE_OF_BLOCK, 0, SIZE_OF_BLOCK,
								SIZE_OF_BLOCK));
						Ship.setPosition(SIZE_OF_BLOCK + i * SIZE_OF_BLOCK, SIZE_OF_BLOCK + j * SIZE_OF_BLOCK);
						MainWindow.draw(Ship);

						Ship.setTextureRect(IntRect(viewSecond[i][j] * SIZE_OF_BLOCK, 0, SIZE_OF_BLOCK,
								SIZE_OF_BLOCK));
						Ship.setPosition(13 * SIZE_OF_BLOCK + i * SIZE_OF_BLOCK, SIZE_OF_BLOCK + j * SIZE_OF_BLOCK);
						MainWindow.draw(Ship);

				}
		}

		MainWindow.display();

}

//--------------------------------------------------------------------------------
void PresBatel(int viewFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int viewSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int shipLocateFirst[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		int shipLocateSecond[COUNT_OF_SHIPS][COUNT_OF_SHIPS],
		Vector2i MouseLocate, int& Who) {

		int MouseX = MouseLocate.x / SIZE_OF_BLOCK,
				MouseY = MouseLocate.y / SIZE_OF_BLOCK;

		if(MouseX >= 1 && MouseX <= 10 &&
				MouseY >= 1 && MouseY <= 10 &&
				Who == 2) {
				MouseX--;
				MouseY--;
				if(viewFirst[MouseX][MouseY] == 0) {
						if(shipLocateFirst[MouseX][MouseY] == -1) {
								viewFirst[MouseX][MouseY] = 1;
								Who = 1;
						} else {
								shipLocateFirst[MouseX][MouseY] += 10;
								if(isClearAround(shipLocateFirst, MouseX, MouseY, shipLocateFirst[MouseX][MouseY])) {
										std::cout << "Around clear" << std::endl;

										int is = 0;
										for(int i = 0; i < COUNT_OF_SHIPS; i++) {
												for(int j = 0; j < COUNT_OF_SHIPS; j++) {
														if(shipLocateFirst[i][j] == ( shipLocateFirst[MouseX][MouseY] - 10 )) {
																is = 1;
																std::cout << "Iteration is" << std::endl;
														}
												}
										}
										if(is == 0) {
												std::cout << "not is" << std::endl;
												for(int i = 0; i < COUNT_OF_SHIPS; i++) {
														for(int j = 0; j < COUNT_OF_SHIPS; j++) {
																if(shipLocateFirst[i][j] == ( shipLocateFirst[MouseX][MouseY] )) {
																		viewFirst[i][j] = 3;
																}
														}
												}
												AroundDot(viewFirst);
										} else {
												std::cout << "is" << std::endl;
												viewFirst[MouseX][MouseY] = 2;
										}
								} else {
										viewFirst[MouseX][MouseY] = 2;
								}
						}
				} else return;
		}

		if(MouseX >= 13 && MouseX <= 23 &&
				MouseY >= 1 && MouseY <= 10 &&
				Who == 1) {
				MouseX -= 13;
				MouseY--;
				if(viewSecond[MouseX][MouseY] == 0) {
						if(shipLocateSecond[MouseX][MouseY] == -1) {
								viewSecond[MouseX][MouseY] = 1;
								Who = 2;
						} else {
								shipLocateSecond[MouseX][MouseY] += 10;
								if(isClearAround(shipLocateSecond, MouseX, MouseY, shipLocateSecond[MouseX][MouseY])) {
										std::cout << "Around clear" << std::endl;

										int is = 0;
										for(int i = 0; i < COUNT_OF_SHIPS; i++) {
												for(int j = 0; j < COUNT_OF_SHIPS; j++) {
														if(shipLocateSecond[i][j] == ( shipLocateSecond[MouseX][MouseY] - 10 )) {
																is = 1;
																std::cout << "Iteration is" << std::endl;

														}
												}
										}
										if(!is) {
												std::cout << "not is" << std::endl;
												for(int i = 0; i < COUNT_OF_SHIPS; i++) {
														for(int j = 0; j < COUNT_OF_SHIPS; j++) {
																if(shipLocateSecond[i][j] == ( shipLocateSecond[MouseX][MouseY] )) {
																		viewSecond[i][j] = 3;
																}
														}
												}
												AroundDot(viewSecond);

										} else {
												std::cout << "is" << std::endl;
												viewSecond[MouseX][MouseY] = 2;
										}
								} else {
										viewSecond[MouseX][MouseY] = 2;
								}
						}
				} else return;
		}

}


//--------------------------------------------------------------------------------
void AroundDot(int view[COUNT_OF_SHIPS][COUNT_OF_SHIPS]) {
		for(int i = 0; i < COUNT_OF_SHIPS; i++) {
				for(int j = 0; j < COUNT_OF_SHIPS; j++) {
						if(view[i][j] == 3) {
								if(i > 0 && j > 0 && ( view[i - 1][j - 1] != 3 )) view[i - 1][j - 1] = 1;
								if(j > 0 && ( view[i][j - 1] != 3  )) view[i][j - 1] = 1;
								if(i < 9 && j > 0 && ( view[i + 1][j - 1] != 3  )) view[i + 1][j - 1] = 1;
								if(i > 0 && ( view[i - 1][j] != 3 )) view[i - 1][j] = 1;
								if(i < 9 && ( view[i + 1][j] != 3 )) view[i + 1][j] = 1;
								if(i > 0 && j < 9 && ( view[i - 1][j + 1] != 3  )) view[i - 1][j + 1] = 1;
								if(j < 9 && ( view[i][j + 1] != 3 )) view[i][j + 1] = 1;
								if(i < 9 && j < 9 && ( view[i + 1][j + 1] != 3 )) view[i + 1][j + 1] = 1;
						}
				}
		}
}
