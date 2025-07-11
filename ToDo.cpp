#include "ToDo.h"
#include <QFile>
#include <QDebug>
#include <QTimer>


ToDo::ToDo(QWidget *parent)
    : QWidget(parent), ui(new Ui::ToDoClass())
{
    ui->setupUi(this);


    // ���õķ����ǣ�
    // 1. �������Զ����ӣ��ֶ�����������Ҫ���źŲ�
    //connect(ui->btnAdd, &QPushButton::clicked, this, &ToDo::on_btnAdd_clicked);
    //connect(ui->btnDelete, &QPushButton::clicked, this, &ToDo::on_btnDelete_clicked);


	loadTasks();  // ��������
}

ToDo::~ToDo()
{
    saveTasks();  // �ر�ʱ��������
	delete ui;    // ɾ��UI����
}

// �������
void ToDo::on_btnAdd_clicked()
{
    QString task = ui->lineEditInput->text().trimmed();
    
    if (!task.isEmpty()) {
		ui->listWidgetTasks->addItem(task);
        ui->lineEditInput->clear();  // ��������
		saveTasks();                 // ��������
    }
}


//ɾ��ѡ������
void ToDo::on_btnDelete_clicked() {
    int row = ui->listWidgetTasks->currentRow();
    qDebug() << "Delete clicked, row:" << row << "count:" << ui->listWidgetTasks->count();
    if (row >= 0) {
        // ����ɾ����ť
		//ui->btnDelete->setEnabled(false);

        delete ui->listWidgetTasks->takeItem(row);
        saveTasks();
        qDebug() << "After delete, count:" << ui->listWidgetTasks->count();

    }
}

//���������ļ�
void ToDo::saveTasks() {
	QFile file(saveFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < ui->listWidgetTasks->count(); ++i) {
            out << ui->listWidgetTasks->item(i)->text() << "\n";
        }
        file.close();
    }
}

// ���ļ���������
void ToDo::loadTasks() {
    QFile file(saveFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString task = in.readLine();
            if (!task.isEmpty()) {
                ui->listWidgetTasks->addItem(task);
            }
        }
        file.close();
    }
}

