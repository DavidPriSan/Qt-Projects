#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFileDialog>
#include <QDir>
#include <QByteArray>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QCloseEvent>
#include "scribblearea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    ScribbleArea *scribbleArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};
#endif // MAINWINDOW_H
