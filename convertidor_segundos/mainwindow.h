#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Macro con código necesario para usar slots y signals

public:
    MainWindow(QWidget *parent = nullptr); // Constructor de clase que genera la ventana
    ~MainWindow(); // Destructor

private slots:
    void on_boton_clicked();

private:
    Ui::MainWindow *ui; // Puntero que representa la UI, desde el que acceder a sus elementos
};
#endif // MAINWINDOW_H
