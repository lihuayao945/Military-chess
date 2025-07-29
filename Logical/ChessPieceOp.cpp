#include "ChessPieceOp.h"
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QEvent>
#include <QMouseEvent>
#include<sstream>

ChessPieceOp::ChessPieceOp(QObject* parent) : QObject(parent) {}

ChessPieceOp::~ChessPieceOp() {}

void ChessPieceOp::setupChessPieces(QGridLayout* layout1, QGridLayout* layout2, QWidget* parent, const std::array<std::array<int, 5>, 12>& pieceArray) {
    qDeleteAll(layout1->children());
    qDeleteAll(layout2->children());

    layout1->setContentsMargins(0, 0, 0, 0);
    layout1->setHorizontalSpacing(35);
    layout1->setVerticalSpacing(0);

    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->setHorizontalSpacing(35);
    layout2->setVerticalSpacing(0);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int value = pieceArray[row][col];
            QString imagePath = QString(":/new/piece/%1.png").arg(value);

            QLabel* pieceLabel = new QLabel(parent);
            pieceLabel->setFixedSize(pieceWidth, pieceHeight);

            QPixmap piecePixmap(imagePath);

            // 检查图片是否有效
            if (!piecePixmap.isNull()) {
                pieceLabel->setPixmap(piecePixmap.scaled(pieceWidth, pieceHeight, Qt::KeepAspectRatio));
            } else {
                // 图片加载失败，设置为空图片或者其他默认行为
                pieceLabel->setPixmap(QPixmap()); // 或者使用默认图片
            }

            pieceLabel->setAlignment(Qt::AlignCenter);

            // 设置用户数据保存行列信息
            pieceLabel->setProperty("row", row);
            pieceLabel->setProperty("col", col);

            // 添加事件过滤器
            pieceLabel->installEventFilter(this);

            if (row < 6) {
                layout1->addWidget(pieceLabel, row, col);
            } else {
                layout2->addWidget(pieceLabel, row - 6, col);
            }
        }
    }

    // 强制刷新布局
        layout1->update();
        layout2->update();
        parent->repaint();  // 重新绘制主窗口
}


bool ChessPieceOp::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* pieceLabel = qobject_cast<QLabel*>(obj);
        if (pieceLabel) {
            int row = pieceLabel->property("row").toInt();
            int col = pieceLabel->property("col").toInt();
            emit pieceClicked(row, col); // 发送信号
        }
    }
    return QObject::eventFilter(obj, event);
}

std::array<std::array<int, 5>, 12> ChessPieceOp::toArray(std::string status){
    std::array<std::array<int, 5>, 12> Board;
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
    return Board;
}
