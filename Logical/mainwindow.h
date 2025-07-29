#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// 前向声明 Form 类
class Form;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int value = 0 ,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPieceClicked(int row, int col);
    void onPushButtonClicked(); // 按钮点击事件

private:
    Ui::MainWindow *ui;
    Form *form;

//    void setupChessPieces1();
//    void setupChessPieces2();
};
#endif // MAINWINDOW_H
