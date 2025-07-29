#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "mainwindow.h" // 引入MainWindow类

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked(); // 玩家对战按钮槽函数
    void on_pushButton_2_clicked(); // 玩家对战按钮槽函数
    void on_pushButton_3_clicked(); // 玩家对战按钮槽函数

private:
    Ui::Form *ui;
    MainWindow *mainWindow; // 用于跳转到 MainWindow 的指针
};

#endif // FORM_H
