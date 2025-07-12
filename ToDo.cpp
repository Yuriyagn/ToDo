#include "ToDo.h"
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QShortcut>
#include <QListWidgetItem>

ToDo::ToDo(QWidget *parent)
    : QWidget(parent), ui(new Ui::ToDoClass())
{
    ui->setupUi(this);

    // 添加快捷键 包含小键盘的回车键
    QShortcut* addShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(addShortcut, &QShortcut::activated, this, &ToDo::on_btnAdd_clicked);

    // 添加Enter键快捷键支持
    QShortcut* enterShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    connect(enterShortcut, &QShortcut::activated, this, &ToDo::on_btnAdd_clicked);

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
        // 检查是否已经存在相同的任务
        bool taskExists = false;
        for (int i = 0; i < ui->listWidgetTasks->count(); ++i) {
            if (ui->listWidgetTasks->item(i)->text() == task) {
                taskExists = true;
                break;
            }
        }
        
        if (!taskExists) {
            ui->listWidgetTasks->addItem(task);
            ui->lineEditInput->clear();  // 清空输入框
            saveTasks();                 // 保存任务
            qDebug() << "Task added:" << task;
        } else {
            qDebug() << "Task already exists:" << task;
            ui->lineEditInput->selectAll(); // 选中文本便于用户修改
        }
    }
}


//删除选中任务
void ToDo::on_btnDelete_clicked() {
    int row = ui->listWidgetTasks->currentRow();
    if (row >= 0) {
        delete ui->listWidgetTasks->takeItem(row);
        saveTasks();
        qDebug() << "Task deleted at row:" << row;
    } else {
        qDebug() << "No task selected for deletion";
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
        qDebug() << "Tasks saved successfully to" << saveFilePath;
    } else {
        qDebug() << "Failed to save tasks to" << saveFilePath << "Error:" << file.errorString();
    }
}

// 从文件加载任务
void ToDo::loadTasks() {
    QFile file(saveFilePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString task = in.readLine().trimmed();
            if (!task.isEmpty()) {
                ui->listWidgetTasks->addItem(task);
            }
        }
        file.close();
        qDebug() << "Tasks loaded successfully from" << saveFilePath;
    } else {
        qDebug() << "No existing task file found or failed to open:" << saveFilePath;
    }
}

void ToDo::on_btnOnTop_clicked()
{
    Qt::WindowFlags flags = windowFlags();

    if (isOnTop) {
        flags &= ~Qt::WindowStaysOnTopHint; // 取消置顶
        ui->btnOnTop->setText(QString::fromLocal8Bit("置顶"));
    }
    else {
        flags |= Qt::WindowStaysOnTopHint; // 设置置顶
        ui->btnOnTop->setText(QString::fromLocal8Bit("取消置顶"));
    }

    setWindowFlags(flags);
    isOnTop = !isOnTop; // 切换置顶状态
    show(); // 重新显示窗口以应用新的标志
    raise(); // 确保窗口在最上层
}

// 双击编辑任务
void ToDo::on_listWidgetTasks_itemDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        QString oldText = item->text();
        ui->lineEditInput->setText(oldText);
        ui->lineEditInput->setFocus();
        ui->lineEditInput->selectAll();
        
        // 删除原任务，用户修改后重新添加
        int row = ui->listWidgetTasks->row(item);
        delete ui->listWidgetTasks->takeItem(row);
        saveTasks();
    }
}

