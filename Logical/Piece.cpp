#include "Piece.h"

// ��ȡ���ӵȼ�  
int Piece::getLevel() const {
	return level;
}

// ��ȡ�����������  
int Piece::getPlayer() const {
	return player;
}

// ��ȡ����״̬  
int Piece::getIsFaceUp() const {
	return isFaceUp;
}

// �������ӵȼ�  
void Piece::setLevel(int levelRet) {
	level = levelRet;
}

// ���������������  
void Piece::setPlayer(int playerRet) {
	player = playerRet;
}

// ���÷���״̬  
void Piece::setIsFaceUp(int isFaceUpRet) {
	isFaceUp = isFaceUpRet;
}

// ��������λ��  
void Piece::setPosition(int xRet, int yRet) {
	x = xRet;
	y = yRet;
}
