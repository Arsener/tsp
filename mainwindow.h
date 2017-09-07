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
#include <QPointF>
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
    void startLinking(int *ans);
    void prepareLinking();
    void setProgressBar(int value);
    void setFileDirectory();
    void setChecked(int state);

private:
    Ui::MainWindow *ui;
    MyThread *t;
    int pointNumber;
    bool linking = false;
    bool painted = false;
    bool file = false;
    QString fileDirectory;
};

#endif // MAINWINDOW_H
