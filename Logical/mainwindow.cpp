#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ChessPieceOp.h"
#include "form.h"
#include"Game.h"
#include <iostream>
#include <array>

MainWindow::MainWindow(int value, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , form(nullptr) // 初始化 form 为 nullptr
{
    ui->setupUi(this);
        // 连接按钮点击事件
           // connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);

            ui->setupUi(this);
            this->show();

                // 初始化游戏逻辑和棋子操作类
                Game gm;
                ChessPieceOp* chessPieceOp = new ChessPieceOp(this);
                std::cout<<"value的值为"<<value;

                // gm.init(1); // 初始化棋盘
                gm.init(value);

                while (true) {
                    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
                    // 2. 检查胜利条件
                    if (gm.win()) {
                        std::cout << "Game Over: You Win!" << std::endl;
                        ui->statusbar->showMessage("游戏胜利！", 5000);
                        break;
                    }

                    // 1. 获取棋盘信息并打印
                    std::array<std::array<int, 5>, 12> Board = chessPieceOp->toArray(gm.getBoardDetail());

                    std::cout << "Board contents:" << std::endl;
                    for (const auto& row : Board) {
                        for (const auto& element : row) {
                            std::cout << element << " ";
                        }
                        std::cout << std::endl;
                    }

                    // 更新棋盘显示
                    chessPieceOp->setupChessPieces(ui->gridLayout_1, ui->gridLayout_2, this, Board);

                    // 3. 用户选择和操作
                    while (true) {
                        // 从屏幕获取用户选择的棋子
                        int x = -1, y = -1;
                        bool validSelection = false;

                        connect(chessPieceOp, &ChessPieceOp::pieceClicked, this, [&x, &y, &validSelection](int row, int col) {
                            x = row;
                            y = col;
                            validSelection = true; // 标记为有效选择
                        });

                        // 等待用户点击
                        while (!validSelection) {
                            QCoreApplication::processEvents(); // 保证事件循环正常运行
                        }

                        // 用户选择棋子
                        int res = gm.choicePiece(x, y);
                        if (res == 0) {
                            // 未选择有效棋子，提示
                            ui->statusbar->showMessage("请选择有效的棋子", 2000);
                            continue;
                        } else if (res == 1) {
                            // 有效选择，无需移动
                            break;
                        } else if (res == 2) {
                            // 移动棋子
                            int nextX = -1, nextY = -1;
                            bool validMove = false;

                            connect(chessPieceOp, &ChessPieceOp::pieceClicked, this, [&nextX, &nextY, &validMove](int row, int col) {
                                nextX = row;
                                nextY = col;
                                validMove = true; // 标记为有效移动
                            });

                            // 等待用户点击目标位置
                            while (!validMove) {
                                QCoreApplication::processEvents();
                            }

                            if (gm.movePiece(nextX, nextY)) {
                                ui->statusbar->showMessage("棋子移动成功", 2000);
                                break; // 退出移动循环
                            } else {
                                ui->statusbar->showMessage("棋子移动失败，请重试", 2000);
                            }
                        }
                    }

                    // 4. AI 操作
                    if(value != 1){
                        gm.AIOperation();
                        std::array<std::array<int, 5>, 12> AIBoard = chessPieceOp->toArray(gm.getBoardDetail());
                        chessPieceOp->setupChessPieces(ui->gridLayout_1, ui->gridLayout_2, this, AIBoard);
                    }
                }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPieceClicked(int row, int col)
{
//    // 打印点击位置，或者执行其他逻辑
//    std::cout << "Piece clicked at row: " << row << ", col: " << col << std::endl;
}

void MainWindow::onPushButtonClicked()
{
    // 打开 Form 界面
    if (!form) {
        form = new Form(this); // 设置父级，确保生命周期受控
    }
    form->show();

    // 隐藏 MainWindow 界面
    this->hide();
}
