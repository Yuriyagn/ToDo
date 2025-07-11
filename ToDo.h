#pragma once

#include <QtWidgets/QWidget>
#include "ui_ToDo.h"
#include <iostream>
using namespace std;



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

private:
    Ui::ToDoClass* ui;
	const QString saveFilePath = "tasks.txt"; // 保存任务的文件路径
};

