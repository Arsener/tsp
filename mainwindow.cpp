#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette Pal(palette()); // TODO: learn this

    Pal.setColor(QPalette::Background, Qt::white);
    ui->paintedWidget->setAutoFillBackground(true);
    ui->paintedWidget->setPalette(Pal);

    ui->progressBar->setRange(0, Tsp::MAXGENERATE);
    ui->progressBar->setValue(0);

    QFile dirctoryFile("C:\\Users\\arsener\\Documents\\Qt\\tsp\\file directory.txt");
    if(!dirctoryFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream txtInput(&dirctoryFile);
        fileDirectory = txtInput.readLine();
    }
    dirctoryFile.close();

    t = new MyThread();

    connect(ui->paintPointsButton, SIGNAL(clicked()), this, SLOT(startPainting()));
    connect(ui->linkButton, SIGNAL(clicked()), this, SLOT(prepareLinking()));
    connect(t, SIGNAL(returnResult(int*)), this, SLOT(startLinking(int*)));
    connect(t, SIGNAL(returnProgress(int)), this, SLOT(setProgressBar(int)));
    connect(ui->setFileAction, SIGNAL(triggered(bool)), this, SLOT(setFileDirectory()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete t;
}

void MainWindow::startPainting()
{
    if(linking)
    {
        QMessageBox::warning(this, "Error!", "You can't repaint now!");
        return;
    }
    else
    {
        painted = true;
        if(ui->numberLineEdit->text() == "")
        {
            QMessageBox::warning(this, "Error!", "Please input the number!");
            return;
        }

        if(ui->xPosLineEdit->text() == "" || ui->yPosLineEdit->text() == "")
        {
            QMessageBox::warning(this, "Error!", "Please input your position!");
            return;
        }
        int number = ui->numberLineEdit->text().toInt();

        int xPos = ui->xPosLineEdit->text().toInt();
        int yPos = ui->yPosLineEdit->text().toInt();

        if(number < 0)
        {
            QMessageBox::warning(this, "Error!", "The number of points must be largger than 0 and less than 100!");
            return;
        }

        if(xPos < 0 || xPos >= 500 || yPos < 0 || yPos >= 400)
        {
            QMessageBox::warning(this, "Error!", "Your are not in the right position!");
            return;
        }

        ui->progressBar->setValue(0);
        ui->paintedWidget->setPointsNumber(number, xPos, yPos);
        ui->paintedWidget->setDraw(true);
        ui->paintedWidget->setLink(false);
        ui->paintedWidget->update();
    }
}

void MainWindow::prepareLinking()
{
    if(!painted)
    {
        QMessageBox::warning(this, "Error!", "Please paint some points first!");
        return;
    }

    if(linking)
    {
        QMessageBox::warning(this, "Error!", "I'm busy now!");
        return;
    }

    linking = true;
    ui->paintedWidget->setDraw(false);
    ui->paintedWidget->setLinking(true);
    Tsp *tsp = new Tsp(ui->numberLineEdit->text().toInt() + 1, ui->paintedWidget->getPoints());
    t->setAttr(tsp, ui->numberLineEdit->text().toInt() + 1, ui->paintedWidget->getPoints());
    t->start();
}

void MainWindow::startLinking(int *ans)
{
    ui->paintedWidget->setAns(ans);
    ui->paintedWidget->setLinking(false);
    ui->paintedWidget->setLink(true);
    ui->paintedWidget->update();


    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save File"),
        fileDirectory,
        tr("*.txt")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QFile f(filename);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        else
        {
            f.open(QIODevice::WriteOnly | QIODevice::Text);

            int startPoint;
            int pointsNumber = ui->numberLineEdit->text().toInt() + 1;
            for(int i = 0; i < pointsNumber; i++)
            {
                if(ans[i] == pointsNumber - 1)
                {
                    startPoint = i;
                    break;
                }
            }

            QTextStream txtOutput(&f);
            for(int i = startPoint; i < pointsNumber; i++)
            {
                QString currentPoint("(" + QString::number(ui->paintedWidget->getPoints()[i].rx()) + "," + QString::number(ui->paintedWidget->getPoints()[i].ry()) + ")\n");
                txtOutput << currentPoint;
            }
            for(int i = 0; i < startPoint; i++)
            {
                QString currentPoint("(" + QString::number(ui->paintedWidget->getPoints()[i].rx()) + "," + QString::number(ui->paintedWidget->getPoints()[i].ry()) + ")\n");
                txtOutput << currentPoint;
            }

            f.close();
        }
    }
    linking = false;
}

void MainWindow::setProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::setFileDirectory()
{
    QString tmpFileDirectory = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), fileDirectory, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(tmpFileDirectory.trimmed() != "")
    {
        fileDirectory = tmpFileDirectory;
    }
    QFile dirctoryFile("C:\\Users\\arsener\\Documents\\Qt\\tsp\\file directory.txt");
    if(!dirctoryFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream txtoutput(&dirctoryFile);
        QString dir(fileDirectory);
        txtoutput << dir;
    }
    dirctoryFile.close();
}
