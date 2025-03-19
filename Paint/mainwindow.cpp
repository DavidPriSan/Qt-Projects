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

void MainWindow::createActions()
{
    // Abrir archivos
    openAct = new QAction(tr("&Open"), this); // Acción
    openAct->setShortcut(QKeySequence::Open); // Atajo
    connect(openAct, SIGNAL(triggered()), this, SLOT(open())); // Asocia acción al SLOT
    // Lista de formatos permitidos (Guardar como)
    foreach(QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper()); // Formato
        QAction *action = new QAction(text, this); // Acción
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save())); // Asocia acción al SLOT
        saveAsActs.append(action);
    }
    // Imprimir
    printAct = new QAction(tr("&Print..."), this); // Acción
    connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print())); // Asocia acción al SLOT
    // Salir
    exitAct = new QAction(tr("&Exit"), this); // Acción
    exitAct->setShortcut(QKeySequence::Quit); // Atajo
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close())); // Asocia acción al SLOT

    // Cambiar color del pincel
    penColorAct = new QAction(tr("&Pen Color..."), this); // Acción
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor())); // Asocia acción al SLOT
    // Cambiar grosor del pincel
    penWidthAct = new QAction(tr("Pen &Width..."), this); // Acción
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth())); // Asocia acción al SLOT

    // Limpiar lienzo
    clearScreenAct = new QAction(tr("&Clear screen..."), this); // Acción
    clearScreenAct->setShortcut(tr("Ctrl+L")); // Atajo
    connect(clearScreenAct, SIGNAL(triggered()), scribbleArea, SLOT(clearImage())); // Asocia acción al SLOT

    // About
    aboutAct = new QAction(tr("&About..."), this); // Acción
    connect(aboutAct, SIGNAL(triggered()), SLOT(about())); // Asocia acción al SLOT

    // About Qt
    aboutQtAct = new QAction(tr("About &Qt..."), this); // Acción
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt())); // Asocia acción al SLOT
}

void MainWindow::createMenus()
{
    // Guardar como
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsActs)
        saveAsMenu->addAction(action);
    // Menú archivo
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    // Menú opciones
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Menú ayuda
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // Barra
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave()
{
    // Advertencia salir sin guardar
    if(scribbleArea->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Scribble"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save){
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    // Guardar archivo
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2;; All Files(*")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}
