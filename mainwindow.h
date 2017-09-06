#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintedwidget.h"
#include "mythread.h"
#include "tsp.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QPalette>
#include <QTextStream>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startPainting();
    void startLinking(int *ans);
    void prepareLinking();
    void setProgressBar(int value);

private:
    Ui::MainWindow *ui;
    MyThread *t;
    bool linking = false;
};

#endif // MAINWINDOW_H
