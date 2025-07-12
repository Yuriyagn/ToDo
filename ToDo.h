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
    void on_btnAdd_clicked();          //�������
    void on_btnDelete_clicked();      //ɾ������
    void saveTasks();                 //��������
    void loadTasks();                 //��������
    void on_btnOnTop_clicked();       // �������ö�
    void on_listWidgetTasks_itemDoubleClicked(QListWidgetItem *item); // ˫���༭����

private:
    Ui::ToDoClass* ui;
	const QString saveFilePath = "tasks.txt"; // ����������ļ�·��
	bool isOnTop = false;              // �����Ƿ��ö���־
};

