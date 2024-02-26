#include <QFileDialog>
#include "main_window.h"
#include "draw_figure.h"
#include <iostream>

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG == 1
#include <stdio.h>
#endif
 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(300, 300, 2000, 1200);
    scene = NULL;
    start_init_figure(figure);
}
 
MainWindow::~MainWindow()
{
    free_data_figure(figure);
    delete ui;
}

err_t MainWindow::set_scene_and_draw()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-ui->graphicsView->width() / 2, -ui->graphicsView->height() / 2, 
    ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    err_t rc = draw_figure(*scene, figure);
    if (rc != OK)
        show_err(rc);
    return rc;
}

err_t MainWindow::check_figure_load()
{
    if (figure.points.len == 0 || figure.points.arr == NULL || figure.links.len == 0 || figure.links.arr == NULL)
    {
        show_err(ERR_FIGURE_NOT_LOADED);
        return ERR_FIGURE_NOT_LOADED;
    }
    return OK;
}

void MainWindow::on_load_btn_clicked()
{
#if DEBUG
    puts("LOAD_BTN_CLICKED: ");
#endif

    // Загрузка данных
    QString str_filename = QFileDialog::getOpenFileName(this, "Open Data Figure", "./data", "Data Files (*.txt)");
    char *filename = new char[str_filename.toStdString().length() + 1];
    strcpy(filename, str_filename.toStdString().c_str());
#if DEBUG
    printf("FILENAME: %s\n", filename);
#endif

    err_t rc = load_figure(filename, figure);
    if (rc != OK)
    {
        show_err(rc);
        return;
    }
    //

    // Определение сцены и рисование фигуры
    set_scene_and_draw();
    //
}

void MainWindow::on_shift_btn_clicked()
{
#if DEBUG
    puts("SHIFT_BTN_CLICKED: ");
#endif
    // Проверка, загружена ли фигура
    err_t rc = check_figure_load();
    if (rc != OK)
        return;
    //
    // Считывание данных введенных пользователем (смещения)
    double dx, dy, dz;
    dx = ui->dx_dsp->value();
    dy = -ui->dy_dsp->value();
    dz = ui->dz_dsp->value();
    //
    // Смещаем фигуру
    rc = shift_figure(figure.points, dx, dy, dz);
    if (rc != OK)
    {
        show_err(rc);
        return;
    }
    //

    // Определение сцены и рисование фигуры
    set_scene_and_draw();
    //
}

void MainWindow::on_rotate_btn_clicked()
{
#if DEBUG
    puts("ROTATE_BTN_CLICKED: ");
#endif
    // Проверка, загружена ли фигура
    err_t rc = check_figure_load();
    if (rc != OK)
        return;
    //
    // Считывание данных введенных пользователем (углы поворота и цент вращения)
    double x_angle, y_angle, z_angle;
    x_angle = ui->x_angle_dsp->value();
    y_angle = ui->y_angle_dsp->value();
    z_angle = ui->z_angle_dsp->value();
    point_t center;
    center.x = ui->cx_dsp->value();
    center.y = ui->cx_dsp->value();
    center.z = ui->cx_dsp->value();
    //
    // Поворот фигуры
    rc = rotate_figure(figure.points, center, x_angle, y_angle, z_angle);
    if (rc != OK)
    {
        show_err(rc);
        return;
    }
    //

    // Определение сцены и рисование фигуры
    set_scene_and_draw();
    //
}

void MainWindow::on_scaling_btn_clicked()
{
#if DEBUG
    puts("SCALING_BTN_CLICKED: ");
#endif

    // Проверка, загружена ли фигура
    err_t rc = check_figure_load();
    if (rc != OK)
        return;
    //
    // Считывание данных введенных пользователем (коэффиценты масштабирования и цент вращения)
    double kx, ky, kz;
    kx = ui->kx_dsp->value();
    ky = ui->ky_dsp->value();
    kz = ui->kz_dsp->value();
    point_t center;
    center.x = ui->cx_dsp->value();
    center.y = ui->cx_dsp->value();
    center.z = ui->cx_dsp->value();
    //

    // масштабирование фигуры
    rc = scale_figure(figure.points, center, kx, ky, kz);
    if (rc != OK)
    {
        show_err(rc);
        return;
    }
    //

    // Определение сцены и рисование фигуры
    set_scene_and_draw();
    //
}


