#ifndef EASYAI_H
#define EASYAI_H
#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <sstream>
#include <set>
#include "AI.h" // 引入基类头文件

class EasyAI : public AI {
public:
    std::string getNextStep(Board board) override;
private:
	void  bfsToTarget(int startX, int startY, int targetX, int targetY, int nowBoard[12][5], int& stepNum, int step[4]);
	bool isValidMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY);
	bool isValidJumpMove(int x, int y, int nowBoard[12][5], int currentLevel, int prevX, int prevY);
};

#endif // EASYAI_H

