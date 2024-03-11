#pragma once
 
#include <QMainWindow>
#include "ui_main_window.h"
#include "select_act.h" 

 
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

    void on_select_color_btn_clicked();

    void start_init_draw_data();

    void set_scene();

private:
    Ui::MainWindow *ui;
    action_data_t action_data;
    // QGraphicsScene *scene;
    draw_data_t draw_data;
};
