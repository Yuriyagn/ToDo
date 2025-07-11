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
    void on_btnAdd_clicked();          //�������
	void on_btnDelete_clicked();      //ɾ������
	void saveTasks();                 //��������
	void loadTasks();                 //��������

private:
    Ui::ToDoClass* ui;
	const QString saveFilePath = "tasks.txt"; // ����������ļ�·��
};

