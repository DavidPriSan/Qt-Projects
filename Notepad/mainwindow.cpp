#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // Para que el text edit ocupe toda la ventana
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered() // Crear nuevo archivo
{
    // Limpia
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered() // Abrir archivo
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file"); // Ventana examinar
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){ // Abrir el archivo y comprobar errores
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName); // Nombre de archivo en título de ventana
    QTextStream in(&file); // Interfaz para leer texto
    QString text = in.readAll(); // Lee el archivo
    ui->textEdit->setText(text); // Asigna el contenido al text edit
    file.close();
}


void MainWindow::on_actionSave_as_triggered() // Guardar archivo
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as"); // Ventana gaurdado
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){ // Abrir el archivo y comprobar errores
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName); // Nombre de archivo en título de ventana
    QTextStream out(&file); // Interfaz para escribir texto
    QString text = ui->textEdit->toPlainText(); // Convierte el texto
    out << text; // Guarda el texto en el archivo
    file.close();
}


void MainWindow::on_actionPrint_triggered() // Imprimir
{
    QPrinter printer;
    printer.setPrinterName("Printer Name"); // Nombre impresora
    QPrintDialog pDialog(&printer, this); // Ventana imprimir
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access printer");
        return;
    }
    ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered() // Salir
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered() // Copiar
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered() // Pegar
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered() // Cortar
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered() // Deshacer
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered() // Rehacer
{
    ui->textEdit->redo();
}

