#pragma once

#include <QtWidgets/QWidget>
#include "ui_ToDo.h"



class ToDo : public QWidget
{
    Q_OBJECT

public:
    ToDo(QWidget *parent = nullptr);

    ~ToDo();

private slots:
    void on_btnAdd_clicked();          //添加任务
    void on_btnDelete_clicked();      //删除任务
    void saveTasks();                 //保存任务
    void loadTasks();                 //加载任务
    void on_btnOnTop_clicked();       // 将窗口置顶
    void on_listWidgetTasks_itemDoubleClicked(QListWidgetItem *item); // 双击编辑任务

private:
    Ui::ToDoClass* ui;
	const QString saveFilePath = "tasks.txt"; // 保存任务的文件路径
	bool isOnTop = false;              // 窗口是否置顶标志
};

