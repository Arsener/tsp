#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mythread.h"
#include "paintedwidget.h"
#include <QFile>
#include <QPointF>
#include <QString>
#include <QPalette>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

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
    void clean();
    void startPainting();
    void prepareLinking();
    void setFileDirectory();
    void setChecked(int state);
    void startLinking(int *ans);
    void setProgressBar(int value);

private:
    Ui::MainWindow *ui;
    int pointNumber;
    bool linking = false;
    bool painted = false;
    bool file = false;
    MyThread *t;
    QString fileDirectory;
};

#endif // MAINWINDOW_H
