#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void graficar1();
    void graficar2();
    void compute();
    void suma();
    void resta();
    void mul();
    void div();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
