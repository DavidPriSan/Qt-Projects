#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcVal)); // Asegura el valor inicial a 0.0
    QPushButton *numButtons[10]; // Array con punteros a los botones de números
    for(int i = 0; i < 10; i++){
        // Obtener el botón por el nombre
        QString butName = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        // Asignar SLOT
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    // Asignar SLOT a operaciones (+, -, *, /)
    connect(ui->add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->substract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    // Asignar SLOT a =
    connect(ui->equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    // Asignar SLOT a cambio de signo
    connect(ui->changeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender(); // Botón presionado
    QString butVal = button->text(); // Valor del botón
    QString displayVal = ui->display->text(); // Valor actual
    // Muestra nuevo valor
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){ // Si antes era 0
        ui->display->setText(butVal);
    } else { // Si había un valor distinto de 0
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblNewVal, 'g', 16)); // Máximo de 16 dígitos
    }
}

void Calculator::MathButtonPressed()
{
    // Resetear operación
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    // Obtener valor actual
    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();
    // Obtener botón presionado
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){ // División
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){ // Multiplicación
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){ // Suma
        addTrigger = true;
    } else{ // División
        subTrigger = true;
    }
    ui->display->setText(""); // Limpia el display
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    // Valor actual
    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();
    // Comprueba operación
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){ // Suma
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){ // Resta
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){ // Multiplicación
            solution = calcVal * dblDisplayVal;
        } else{ // División
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->display->setText(QString::number(solution)); // Muestra resultado
}

void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->display->text(); // Valor actual
    QRegularExpression reg("[-]?[0-9.]*"); // Para comprobaciones
    if(reg.match(displayVal).hasMatch()){
        double dblDisplayValue = displayVal.toDouble();
        double dblDisplayValueSign = -1 * dblDisplayValue; // Cambia el signo
        ui->display->setText(QString::number(dblDisplayValueSign)); // Muestra resultado
    }
}
