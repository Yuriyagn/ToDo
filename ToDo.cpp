#include "ToDo.h"
#include <QFile>
#include <QDebug>
#include <QTimer>


ToDo::ToDo(QWidget *parent)
    : QWidget(parent), ui(new Ui::ToDoClass())
{
    ui->setupUi(this);


    // 更好的方法是：
    // 1. 不依赖自动连接，手动连接所有需要的信号槽
    //connect(ui->btnAdd, &QPushButton::clicked, this, &ToDo::on_btnAdd_clicked);
    //connect(ui->btnDelete, &QPushButton::clicked, this, &ToDo::on_btnDelete_clicked);


	loadTasks();  // 加载任务
}

ToDo::~ToDo()
{
    saveTasks();  // 关闭时保存任务
	delete ui;    // 删除UI对象
}

// 添加任务
void ToDo::on_btnAdd_clicked()
{
    QString task = ui->lineEditInput->text().trimmed();
    
    if (!task.isEmpty()) {
		ui->listWidgetTasks->addItem(task);
        ui->lineEditInput->clear();  // 清空输入框
		saveTasks();                 // 保存任务
    }
}


//删除选中任务
void ToDo::on_btnDelete_clicked() {
    int row = ui->listWidgetTasks->currentRow();
    qDebug() << "Delete clicked, row:" << row << "count:" << ui->listWidgetTasks->count();
    if (row >= 0) {
        // 禁用删除按钮
		//ui->btnDelete->setEnabled(false);

        delete ui->listWidgetTasks->takeItem(row);
        saveTasks();
        qDebug() << "After delete, count:" << ui->listWidgetTasks->count();

    }
}

//保存任务到文件
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

// 从文件加载任务
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

