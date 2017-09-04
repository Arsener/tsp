#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintedwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
    QWidget *w;
    PaintedWidget *paintedWidget;
    QLineEdit *numberLineEdit;
    QPushButton *button;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
};

#endif // MAINWINDOW_H
