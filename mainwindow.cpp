#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    w = new QWidget(this);
    setCentralWidget(&w);
//    paintedWidget = new PaintedWidget();
//    numberLineEdit = new QLineEdit();
//    paintPointsButton = new QPushButton();
//    linkButton = new QPushButton();
//    vLayout = new QVBoxLayout();
//    hLayout = new QHBoxLayout();

    QPalette Pal(palette()); // TODO: learn this

    Pal.setColor(QPalette::Background, Qt::white);
    paintedWidget.setAutoFillBackground(true);
    paintedWidget.setPalette(Pal);
//    paintedWidget.show();

    paintPointsButton.setText("Start Painting!");
    linkButton.setText("Start Linking!");
    hLayout.addWidget(&numberLineEdit);
    hLayout.addWidget(&paintPointsButton);
    hLayout.addWidget(&linkButton);
    vLayout.addWidget(&paintedWidget);
    vLayout.addLayout(&hLayout);

    connect(&paintPointsButton, SIGNAL(clicked()), this, SLOT(startPainting()));
    connect(&linkButton, SIGNAL(clicked()), this, SLOT(startLinking()));

    w.setLayout(&vLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPainting()
{
    int number = numberLineEdit.text().toInt();

    if(number < 0)
    {
        QMessageBox::warning(this, "Error!", "The number must be largger than zero!");
        return;
    }
    paintedWidget.setPointsNumber(number);
    paintedWidget.setDraw(true);
    paintedWidget.setLink(false);
    paintedWidget.update();
}


void MainWindow::startLinking()
{
    paintedWidget.setLink(true);
    paintedWidget.setDraw(false);
    paintedWidget.update();
}
