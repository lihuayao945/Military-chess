#ifndef Piece_H  
#define Piece_H

class Piece {
public:
	int level;  // ���ӵȼ������ͣ�  
	int player; // ����������ң�1 = �Ϸ�, 2 = �·���  
	int isFaceUp; // �Ƿ񷭿���0δ���� 1����  
	int x, y;  // ����λ��  
	Piece(int level = 0, int player = 0, int faceUp = 0, int xPos = 0, int yPos = 0): level(level), player(player), isFaceUp(faceUp), x(xPos), y(yPos) {}
	
	int getLevel() const;// ��ȡ���ӵȼ�  
	int getPlayer() const;// ��ȡ�����������  
	int getIsFaceUp() const;// ��ȡ����״̬  
	void setLevel(int levelRet);// �������ӵȼ�  
	void setPlayer(int playerRet);// ���������������  
	void setIsFaceUp(int isFaceUpRet);// ���÷���״̬  
	void setPosition(int xRet, int yRet);// ��������λ��  
};
#endif
