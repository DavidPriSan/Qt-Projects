#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scribblearea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scribbleArea = new ScribbleArea; // Área de dibujo
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Scribble"));
    resize(500,500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{ // Abrir archivo
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open File"), QDir::currentPath());
        if(!fileName.isEmpty()){ // Comprobar que todo ha ido bien
            scribbleArea->openImage(fileName);
        }
    }
}

void MainWindow::save()
{ // Guardar archivo
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{ // Cambiar color del pincel
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if(newColor.isValid()){
        scribbleArea->setPenColor(newColor);
    }
}

void MainWindow::penWidth()
{ // Cambiar ancho del pincel
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width : "),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

void MainWindow::about()
{ // Ventana About
    QMessageBox::about(this, tr("About Scribble"),
                       tr("<p>The <b>Scribble</b> example is awesome</p>"));
}
