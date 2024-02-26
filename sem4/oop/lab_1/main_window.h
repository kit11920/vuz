
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include "ui_main_window.h"
#include "data_figure.h"   

// #define FILENAME "./rect_3d.txt"
#define FILENAME "./pyramid.txt"
 
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 
private slots:
    void on_shift_btn_clicked();

    void on_rotate_btn_clicked();

    void on_scaling_btn_clicked();

    void on_load_btn_clicked();

    err_t set_scene_and_draw();

    err_t check_figure_load();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    figure_t figure;
};
 
#endif // MAINWINDOW_H