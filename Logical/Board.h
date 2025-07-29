#ifndef Board_H  
#define Board_H

#include "Piece.h" 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

class Board {
private:
public:
	int type = 1;
	static const int BOARD_COLS = 5;
	static const int BOARD_ROWS = 12;
	Piece board[BOARD_ROWS][BOARD_COLS];

	void initialize(int type);// ��ʼ������
	void printBoard() const;// ��ӡ��������
	int move(int currentX, int currentY, int nextX, int nextY);// �ƶ�
	int isFaceup(int currentX, int currentY);// �����Ƿ񷭿�
	int getplayer(int xret, int yret);// �����������
	int existPiece(int xret, int yret);// �Ƿ��������
	std::string getBoardState();// ��������״̬
	void setOpen(int x,int y); //�������� 
	int getLevel(int x,int y);
};
#endif
