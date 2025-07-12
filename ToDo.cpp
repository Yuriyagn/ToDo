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

    // ��ӿ�ݼ� ����С���̵Ļس���
    QShortcut* addShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(addShortcut, &QShortcut::activated, this, &ToDo::on_btnAdd_clicked);

    // ���Enter����ݼ�֧��
    QShortcut* enterShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    connect(enterShortcut, &QShortcut::activated, this, &ToDo::on_btnAdd_clicked);

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
        // ����Ƿ��Ѿ�������ͬ������
        bool taskExists = false;
        for (int i = 0; i < ui->listWidgetTasks->count(); ++i) {
            if (ui->listWidgetTasks->item(i)->text() == task) {
                taskExists = true;
                break;
            }
        }
        
        if (!taskExists) {
            ui->listWidgetTasks->addItem(task);
            ui->lineEditInput->clear();  // ��������
            saveTasks();                 // ��������
            qDebug() << "Task added:" << task;
        } else {
            qDebug() << "Task already exists:" << task;
            ui->lineEditInput->selectAll(); // ѡ���ı������û��޸�
        }
    }
}


//ɾ��ѡ������
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

//���������ļ�
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

// ���ļ���������
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
        flags &= ~Qt::WindowStaysOnTopHint; // ȡ���ö�
        ui->btnOnTop->setText(QString::fromLocal8Bit("�ö�"));
    }
    else {
        flags |= Qt::WindowStaysOnTopHint; // �����ö�
        ui->btnOnTop->setText(QString::fromLocal8Bit("ȡ���ö�"));
    }

    setWindowFlags(flags);
    isOnTop = !isOnTop; // �л��ö�״̬
    show(); // ������ʾ������Ӧ���µı�־
    raise(); // ȷ�����������ϲ�
}

// ˫���༭����
void ToDo::on_listWidgetTasks_itemDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        QString oldText = item->text();
        ui->lineEditInput->setText(oldText);
        ui->lineEditInput->setFocus();
        ui->lineEditInput->selectAll();
        
        // ɾ��ԭ�����û��޸ĺ��������
        int row = ui->listWidgetTasks->row(item);
        delete ui->listWidgetTasks->takeItem(row);
        saveTasks();
    }
}

