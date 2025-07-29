#include "Game.h"

using namespace std;

// 初始化棋盘，调用 board 初始化棋盘，type 表示游戏类型
void Game::init(int type) {
    // 假设 Board 类有一个初始化函数，根据游戏类型初始化棋盘
    board.initialize(type);
    currentPlayer = 2;
    // 设置 AI 的难度等
    if (type == 2) {
        ai = new EasyAI();
    } else if (type == 3) {
        ai = new DifficultAI();
    }
}

Game::~Game(){
    delete ai;
}

// 玩家选择棋子
int Game::choicePiece(int x, int y) {
    if (board.existPiece(x,y)) //越界和是否存在棋子判断
    {
        if(!board.isFaceup(x,y))
        {
            if(currentPlayer == board.getplayer(x,y))//写一个找到x,y属于哪个玩家
            {
                currentPlayer = (currentPlayer == 2) ? 1 : 2;
                board.setOpen(x,y);
                return 1;//1代表翻开棋子
            }
            else
            {
                    return 0;//非己方棋子选择无效
            }
        }
        else
        {
            if(currentPlayer == board.getplayer(x,y))
            {
                currentX = x;
                currentY = y;
                return 2;//2代表选择棋子
            }
            else
            {
                    return 0;//非己方棋子选择无效
            }
        }
    }
    else
    {
        return 0;//越界或没有棋子
    }
}

// 移动棋子：玩家尝试移动当前选择的棋子到下一个位置
bool Game::movePiece(int nextX, int nextY) {
        std::cout<<"choice"<<currentX<<"  "<<currentY<<endl;
        std::cout<<"next"<<nextX<<"  "<<nextY<<endl;
        if (board.move(currentX, currentY, nextX, nextY))
        {//铁路，行营，能不能动需要注意
            currentPlayer = (currentPlayer == 2) ? 1 : 2;
            return true;
        }
        return false;
}

// 获取当前棋盘的状态
std::string Game::getBoardDetail() {
    return board.getBoardState(); // 返回的是一个二维数组，有棋子且明面的显示
}

void Game::AIOperation(){
    string nextLo = ai->getNextStep(board);
    array<int, 4> Lo;
    // 使用字符串流来分割字符串
    stringstream ss(nextLo);
    char delimiter;
    // 逐个读取数字并存入数组
    for (int i = 0; i < 4; ++i) {
        ss >> Lo[i];
        ss >> delimiter;  // 跳过逗号
    }
    if(Lo[0] == -1){
        printf("电脑出错了逻辑有误一步不走");
        currentPlayer = 2;
    }else{
        if(Lo[2] == -1){
            std::cout<<"电脑决定翻开棋子,x:"<<Lo[0]<<" y:"<<Lo[1]<<" "<<std::endl;
            board.setOpen(Lo[0],Lo[1]);
            currentPlayer = 2;
        }else{
            std::cout<<"电脑决定移动棋子,Choicex:"<<Lo[0]<<" choicey:"<<Lo[1]<<" nextX"<<Lo[2]<<" nextY"<<Lo[3]<<std::endl;

            board.move(Lo[0],Lo[1],Lo[2],Lo[3]);
            currentPlayer = 2;
        }
    }
}

// 检查当前玩家是否获胜
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
        std::cout<<"上方玩家无棋可动输了"<<endl;
        return true;
    }
    if(num2 == 0)
    {
        std::cout<<"下方玩家无棋可动输了"<<endl;
        return true;
    }
    if(board.getLevel(0,3) != 12)//下方1
    {
        std::cout<<"下方玩家占领了军旗赢了！"<<endl;
         return true;
    }
    if(board.getLevel(11,1) != 12)//下方1
    {
        std::cout<<"上方玩家占领了军旗赢了！"<<endl;
        return true;
    }
}

void Game::printGame(){
    std::string status = board.getBoardState();
    int Board[12][5];
    // 使用字符串流来分割字符串
    std::stringstream ss(status);
    char c;
    // 逐个读取数字并存入数组
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
