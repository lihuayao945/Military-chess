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
    // ��ʼ������,����boardʵ�����̳�ʼ��, type��ʾ��Ϸ���ͣ�0���ˣ�1�򵥣�2���� 
    void init(int type);
    // ��ҵ�һ��ѡ�����ӣ�0����ѡ����Ч��1������δ�������ӣ�2����ѡ���ѷ������� 
    int choicePiece(int x,int y);
    // �ƶ����ӣ���ҳ����ƶ���ǰѡ�����ӵ���һ�� 
    bool movePiece(int nextX, int nextY);
    // ��ȡ��ǰ���̵�״̬
    std::string getBoardDetail();
    //AI����
	void AIOperation(); 
    // ��鵱ǰ����Ƿ��ʤ
    bool win();
    ~Game();
    void printGame();
};
#endif // GAME_H

