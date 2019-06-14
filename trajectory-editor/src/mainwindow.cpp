#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QDir>
#include    <QFileDialog>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , openPath("./")
  , savePath("./")
  , importPath("./")
  , settings(new QSettings)
  , zds_traj1(Q_NULLPTR)
  , zds_traj2(Q_NULLPTR)
{
    ui->setupUi(this);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::slotQuit);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::slotOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::slotSave);
    connect(ui->actionImport_ZDS_route, &QAction::triggered, this, &MainWindow::slotImport);

    openPath = settings->value("openPath", QDir::homePath()).toString();
    savePath = settings->value("savePath", QDir::homePath()).toString();
    importPath = settings->value("importPath", QDir::homePath()).toString();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotQuit()
{
    QApplication::quit();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotOpen()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotSave()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::slotImport()
{
    QString path = QFileDialog::getExistingDirectory(Q_NULLPTR,
                                                     tr("Import ZDS route"),
                                                     importPath);

    if (path.isEmpty())
        return;

    importPath = path;
    settings->setValue("importPath", importPath);

    zds_traj1 = new Trajectory();
    zds_traj1->load(path + QDir::separator() + "route1.trk");

    zds_traj2 = new Trajectory();
    zds_traj2->load(path + QDir::separator() + "route2.trk");
}
