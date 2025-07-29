#ifndef GAME_H
#define GAME_H
#include"Board.h"
#include"AI.h"
#include"EasyAI.h"
#include"DifficultAI.h"
#include <vector>
#include <string>
#include <array>
#include <sstream>

class Game {
private:
	int currentX;
	int currentY;
    Board board;
    AI* ai;
    int currentPlayer;
public:
    // 初始化棋盘,调用board实现棋盘初始化, type表示游戏类型，0人人，1简单，2困难 
    void init(int type);
    // 玩家第一步选择棋子，0代表选择无效，1代表翻开未翻开棋子，2代表选择已翻开棋子 
    int choicePiece(int x,int y);
    // 移动棋子：玩家尝试移动当前选择棋子到下一个 
    bool movePiece(int nextX, int nextY);
    // 获取当前棋盘的状态
    std::string getBoardDetail();
    //AI操作
	void AIOperation(); 
    // 检查当前玩家是否获胜
    bool win();
    ~Game();
    void printGame();
};
#endif // GAME_H

