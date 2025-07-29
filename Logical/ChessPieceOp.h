#ifndef CHESSPIECEOP_H
#define CHESSPIECEOP_H

#include <QObject>
#include <QGridLayout>
#include <array>

class ChessPieceOp : public QObject {
    Q_OBJECT

public:
    ChessPieceOp(QObject* parent = nullptr);
    ~ChessPieceOp();

    void setupChessPieces(QGridLayout* layout1, QGridLayout* layout2, QWidget* parent, const std::array<std::array<int, 5>, 12>& pieceArray);

    bool eventFilter(QObject* obj, QEvent* event);

    std::array<std::array<int, 5>, 12> toArray(std::string status);
signals:
    void pieceClicked(int row, int col);

private:
    const int rows = 12; // 棋盘行数
    const int cols = 5;  // 棋盘列数
    const int pieceWidth = 65; // 棋子宽度
    const int pieceHeight = 50; // 棋子高度
};

#endif // CHESSPIECEOP_H
