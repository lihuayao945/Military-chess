#include "Game.h"

using namespace std;

// ��ʼ�����̣����� board ��ʼ�����̣�type ��ʾ��Ϸ����
void Game::init(int type) {
    // ���� Board ����һ����ʼ��������������Ϸ���ͳ�ʼ������
    board.initialize(type);
    currentPlayer = 2;
    // ���� AI ���Ѷȵ�
    if (type == 2) {
        ai = new EasyAI();
    } else if (type == 3) {
        ai = new DifficultAI();
    }
}

Game::~Game(){
    delete ai;
}

// ���ѡ������
int Game::choicePiece(int x, int y) {
    if (board.existPiece(x,y)) //Խ����Ƿ���������ж�
    {
        if(!board.isFaceup(x,y))
        {
            if(currentPlayer == board.getplayer(x,y))//дһ���ҵ�x,y�����ĸ����
            {
                currentPlayer = (currentPlayer == 2) ? 1 : 2;
                board.setOpen(x,y);
                return 1;//1����������
            }
            else
            {
                    return 0;//�Ǽ�������ѡ����Ч
            }
        }
        else
        {
            if(currentPlayer == board.getplayer(x,y))
            {
                currentX = x;
                currentY = y;
                return 2;//2����ѡ������
            }
            else
            {
                    return 0;//�Ǽ�������ѡ����Ч
            }
        }
    }
    else
    {
        return 0;//Խ���û������
    }
}

// �ƶ����ӣ���ҳ����ƶ���ǰѡ������ӵ���һ��λ��
bool Game::movePiece(int nextX, int nextY) {
        std::cout<<"choice"<<currentX<<"  "<<currentY<<endl;
        std::cout<<"next"<<nextX<<"  "<<nextY<<endl;
        if (board.move(currentX, currentY, nextX, nextY))
        {//��·����Ӫ���ܲ��ܶ���Ҫע��
            currentPlayer = (currentPlayer == 2) ? 1 : 2;
            return true;
        }
        return false;
}

// ��ȡ��ǰ���̵�״̬
std::string Game::getBoardDetail() {
    return board.getBoardState(); // ���ص���һ����ά���飬���������������ʾ
}

void Game::AIOperation(){
    string nextLo = ai->getNextStep(board);
    array<int, 4> Lo;
    // ʹ���ַ��������ָ��ַ���
    stringstream ss(nextLo);
    char delimiter;
    // �����ȡ���ֲ���������
    for (int i = 0; i < 4; ++i) {
        ss >> Lo[i];
        ss >> delimiter;  // ��������
    }
    if(Lo[0] == -1){
        printf("���Գ������߼�����һ������");
        currentPlayer = 2;
    }else{
        if(Lo[2] == -1){
            std::cout<<"���Ծ�����������,x:"<<Lo[0]<<" y:"<<Lo[1]<<" "<<std::endl;
            board.setOpen(Lo[0],Lo[1]);
            currentPlayer = 2;
        }else{
            std::cout<<"���Ծ����ƶ�����,Choicex:"<<Lo[0]<<" choicey:"<<Lo[1]<<" nextX"<<Lo[2]<<" nextY"<<Lo[3]<<std::endl;

            board.move(Lo[0],Lo[1],Lo[2],Lo[3]);
            currentPlayer = 2;
        }
    }
}

// ��鵱ǰ����Ƿ��ʤ
bool Game::win()  {
    int num1 = 0;
    int num2 = 0;
    for(int i = 0;i < 12;i++){
        for(int j = 0;j<5;j++)
        {
            if(board.getplayer(i,j) == 1)
            {
                if(board.getLevel(i,j)>=1&&board.getLevel(i,j)<=10){
                    num1++;
                }
            }
            if(board.getplayer(i,j) == 2)
            {
                if(board.getLevel(i,j)>=1&&board.getLevel(i,j)<=10){
                    num2++;
                }
            }
        }
    }
    if(num1 == 0)
    {
        std::cout<<"�Ϸ��������ɶ�����"<<endl;
        return true;
    }
    if(num2 == 0)
    {
        std::cout<<"�·��������ɶ�����"<<endl;
        return true;
    }
    if(board.getLevel(0,3) != 12)//�·�1
    {
        std::cout<<"�·����ռ���˾���Ӯ�ˣ�"<<endl;
         return true;
    }
    if(board.getLevel(11,1) != 12)//�·�1
    {
        std::cout<<"�Ϸ����ռ���˾���Ӯ�ˣ�"<<endl;
        return true;
    }
}

void Game::printGame(){
    std::string status = board.getBoardState();
    int Board[12][5];
    // ʹ���ַ��������ָ��ַ���
    std::stringstream ss(status);
    char c;
    // �����ȡ���ֲ���������
    for (int i = 0; i < 12; i++) {
        for(int j =0;j< 5;j++){
            ss >> Board[i][j];
            ss >> c;
        }
    }
    for(int i = 0;i<12;i++)
    {
        for(int j = 0;j<5;j++)
        {
            cout<<Board[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
    //board.printBoard();
}
