#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) // Constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Instancia los widgets
}

MainWindow::~MainWindow() // Destructor
{
    delete ui;
}


void MainWindow::on_boton_clicked() // Convertir segundos -> horas, minutos, segundos
{
    // Variables
    short hora, min, seg;

    QString segundosDato = ui->dato->text(); // Obtiene el texto ingresado por el usuario
    long int segundos = segundosDato.toInt(); // Convierte el texto a número

    // Cálculo de horas, minutos y segundos
    seg = segundos % 60;
    min = (segundos / 60) % 60;
    hora = (segundos / 3600);

    // Mostrar resultado
    ui->resultado->setText(QString::number(hora) + " horas, " + QString::number(min) + " minutos, " + QString::number(seg) + " segundos.");
}

