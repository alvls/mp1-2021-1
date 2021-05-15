#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "MyDisplay.h"
#include "MySnake.h"
#include "MyCoordXY.h"
#include <string>

using namespace std;

class MyGame
{
private:
	enum Condition {Ok, Died, Exit, Win};
	int width, height;
	int latency,numfood;
	MyDisplay console;
	MySnake snake;
	unsigned long rating; 
	string nickname;

	void WinnerGame();
	void LoserGame();
	void DrawDisplay();
	void ShowMainMenu();
	MyCoordXY CreateFood();
	void Game();
	void SettingMenu();
	void SetSpeedSnake(int speed) { latency = speed; }
	void SetMapDimensions(int _width, int _height) { width = _width; height = _height; }
	void SetScoreForVictory(int score) { numfood = score; }
	void MapDimensionsMenu();
	void SnakeSpeedMenu();
	void DifficultyMenu();
	void ShowStatistics(int numfruit);
public:
	void MainMenu();
	void TakeNickName(string& str);
	void LogoGame();
	MyGame(MyDisplay& _displ, int _width = 80, int _height = 24, int _latency = 100);
};

#endif __MYGAME_H__
