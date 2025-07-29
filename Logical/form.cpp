#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    mainWindow(nullptr) // 初始化指针
{
    ui->setupUi(this);

    // 连接信号和槽
    connect(ui->pushButton, &QPushButton::clicked, this, &Form::on_pushButton_clicked);
}

Form::~Form()
{
    delete ui;
    if (mainWindow)
        delete mainWindow;
}

void Form::on_pushButton_clicked()
{
    // 创建并显示 MainWindow
    if (!mainWindow) { // 避免重复创建
        mainWindow = new MainWindow(1);
    }
    mainWindow->show(); // 显示 MainWindow 窗口
    this->close(); // 隐藏当前窗口
}

void Form::on_pushButton_2_clicked()
{
    // 创建并显示 MainWindow，并传入值 1
    if (!mainWindow) { // 避免重复创建
        mainWindow = new MainWindow(2); // 传入参数 1
    }
    mainWindow->show(); // 显示 MainWindow 窗口
    this->close(); // 隐藏当前窗口
}

void Form::on_pushButton_3_clicked()
{
    // 创建并显示 MainWindow，并传入值 2
    if (!mainWindow) { // 避免重复创建
        mainWindow = new MainWindow(3); // 传入参数 1
    }
    mainWindow->show(); // 显示 MainWindow 窗口
    this->close(); // 隐藏当前窗口
}

