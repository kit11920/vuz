#include <QFileDialog>
#include <QColorDialog>
#include "main_window.h"

 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(300, 300, 2000, 1200);
    init_action_data(action_data);
    start_init_draw_data();
}
 
MainWindow::~MainWindow()
{
    set_action_to_quit(action_data);
    do_action(action_data);
    delete ui;
}

void MainWindow::start_init_draw_data()
{
    set_scene();
    draw_data.pen = new QPen(Qt::darkBlue, 3);
}

void MainWindow::set_scene()
{
    draw_data.scene = new QGraphicsScene(this);
    draw_data.scene->setSceneRect(-ui->graphicsView->width() / 2, -ui->graphicsView->height() / 2, 
    ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setScene(draw_data.scene);
}

void MainWindow::on_select_color_btn_clicked()
{
    err_t rc = OK;
    QColor color = QColorDialog::getColor(Qt::darkBlue, this, "Вырерите цвет");
    if (color.isValid())
        draw_data.pen = new QPen(color, 3);
    else 
        rc = ERR_SELECT_COLOR;
    
    if (rc == OK)
    {
        set_action_to_draw(action_data, draw_data);
        do_action(action_data);
    }

    if (rc != OK)
        show_err(rc);
}

void MainWindow::on_load_btn_clicked()
{
#if DEBUG
    puts("LOAD_BTN_CLICKED: ");
#endif

    // Выбор файла с данными
    QString str_filename = QFileDialog::getOpenFileName(this, "Open Data Figure", "./data", "Data Files (*.txt)");
    char *filename = new char[str_filename.toStdString().length() + 1];
    strcpy(filename, str_filename.toStdString().c_str());
#if DEBUG
    printf("FILENAME: %s\n", filename);
#endif

    set_action_to_load(action_data, filename);
    err_t rc;
    if ((rc = do_action(action_data)) == OK)
    {
        set_scene();

        set_action_to_draw(action_data, draw_data);
        rc = do_action(action_data);
    }
    if (rc != OK)
        show_err(rc);
}

void MainWindow::on_shift_btn_clicked()
{
#if DEBUG
    puts("SHIFT_BTN_CLICKED: ");
#endif
    // Считывание данных введенных пользователем (смещения)
    shift_data_t shift_data;
    shift_data.dx = ui->dx_dsp->value();
    shift_data.dy = -ui->dy_dsp->value();
    shift_data.dz = ui->dz_dsp->value();
    //

    set_action_to_shift(action_data, shift_data);
    err_t rc;
    if ((rc = do_action(action_data)) == OK)
    {
        set_scene();

        set_action_to_draw(action_data, draw_data);
        rc = do_action(action_data);
    }
    if (rc != OK)
        show_err(rc);
}

void MainWindow::on_rotate_btn_clicked()
{
#if DEBUG
    puts("ROTATE_BTN_CLICKED: ");
#endif
    // Считывание данных введенных пользователем (углы поворота и цент вращения)
    point_t center;
    center.x = ui->cx_dsp->value();
    center.y = ui->cx_dsp->value();
    center.z = ui->cx_dsp->value();
    rotate_data_t rotate_data;
    rotate_data.center = center;
    rotate_data.x_grad = ui->x_angle_dsp->value();
    rotate_data.y_grad = ui->y_angle_dsp->value();
    rotate_data.z_grad = ui->z_angle_dsp->value();
    //
    set_action_to_rotate(action_data, rotate_data);
    err_t rc;
    if ((rc = do_action(action_data)) == OK)
    {
        set_scene();

        set_action_to_draw(action_data, draw_data);
        rc = do_action(action_data);
    }
    if (rc != OK)
        show_err(rc);
}

void MainWindow::on_scaling_btn_clicked()
{
#if DEBUG
    puts("SCALING_BTN_CLICKED: ");
#endif
    // Считывание данных введенных пользователем (коэффиценты масштабирования и цент вращения)
    point_t center;
    center.x = ui->cx_dsp->value();
    center.y = ui->cx_dsp->value();
    center.z = ui->cx_dsp->value();
    scale_data_t scale_data;
    scale_data.center = center;
    scale_data.kx = ui->kx_dsp->value();
    scale_data.ky = ui->ky_dsp->value();
    scale_data.kz = ui->kz_dsp->value();
    //

    set_action_to_scale(action_data, scale_data);
    err_t rc;
    if ((rc = do_action(action_data)) == OK)
    {
        set_scene();

        set_action_to_draw(action_data, draw_data);
        rc = do_action(action_data);
    }
    if (rc != OK)
        show_err(rc);
}


