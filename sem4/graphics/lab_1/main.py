import sys
from PyQt5 import uic
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QTableWidgetItem)
from PyQt5.QtGui import QPainter, QPen, QFont
from PyQt5.QtCore import Qt, QPoint


DEBUG = True

# ERRORS
ERR = 'ERROR: '
ERR_NOT_RECT = ERR + 'Данная точка вместе с уже введенными не может образовать прямоугольник'
ERR_RECT_EXIST_POINT = ERR + 'Данная точка уже определена, если хотите ее изменить, то выберете функцию редактирования '
ERR_EDIT_RECT_POINT = ERR + 'Редактировать точку можно только, когда их введено 1, 2 или 3 шт'
ERR_NO_DATA = ERR + 'Не введена еще ни одна точка'
##


# проверяет, является ли угол 123 = 90град
def if_90_grad(p1, p2, p3):
    # находим вектора
    v12 = (p1[0] - p2[0], p1[1] - p2[1])
    v32 = (p3[0] - p2[0], p3[1] - p2[1])

    # проверяем перпендикулярность угла 123 по скалярному произведению
    return v12[0] * v32[0] + v12[1] * v32[1] == 0


class CanvasWidget(QWidget):
    def __init__(self):
        super().__init__()
        # uic.loadUi('canvas.ui', self)
        
        self.frame_size = 50
        self.k = 1 # коэфицент масштабирования
        self.real_x = self.width()
        self.real_y = self.height()
        self.max_x = self.max_y = self.min_x = self.min_y = self.maxlen_x = self.maxlen_y = None
        self.center = [0, 0]
        self.frame_size = 50
        self.text_height = 25
        self.text_width = 200
        
        self.rectp = dict()
        self.arrp = list()
        self.canvas_rect = dict()
        self.canvas_arr = list()

    def update_sup_data(self):
        self.real_x = self.width()
        self.real_y = self.height()
        self.max_x = max([i[0] for i in self.rectp.values()] + [i[0] for i in self.arrp])
        self.min_x = min([i[0] for i in self.rectp.values()] + [i[0] for i in self.arrp])
        self.max_y = max([i[1] for i in self.rectp.values()] + [i[1] for i in self.arrp])
        self.min_y = min([i[1] for i in self.rectp.values()] + [i[1] for i in self.arrp])
        self.maxlen_x = self.max_x - self.min_x
        self.maxlen_y = self.max_y - self.min_y

    # высчитывает коэффицент масштабирования
    # предполагается что вспомагательные данные обновлены
    def update_koef(self):
        self.k = min((self.real_x - self.frame_size * 2) / self.maxlen_x, (self.real_y - self.frame_size * 2) / self.maxlen_y)

        if DEBUG:
            print(f'{self.update_koef.__name__}:\t self.k: {self.k}, self.frame_size: {self.frame_size}\n'
                  f'(real_x, real_y): {(self.real_x, self.real_y)}\n'
                  f'(maxlen_x, maxlen_y): {(self.maxlen_x, self.maxlen_y)}')

    # предполагается что вспомагательные данные обновлены
    def to_positiv_coords(self):
        plusx = plusy = 0
        if self.min_x < 0:
            plusx = -self.min_x
        if self.min_y < 0:
            plusy = -self.min_y

        for k in self.canvas_rect.keys():
            self.canvas_rect[k][0] += plusx
            self.canvas_rect[k][1] += plusy
        for i in range(len(self.canvas_arr)):
            self.canvas_arr[i][0] += plusx
            self.canvas_arr[i][1] += plusy
        self.center = [plusx, plusy]

        if DEBUG:
            print(f'\n{self.to_positiv_coords.__name__}:\t self.center: {self.center}\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')

    # масштабируем
    def scaling(self):
        for key in self.canvas_rect.keys():
            self.canvas_rect[key] = list(map(lambda x: int(x * self.k), self.canvas_rect[key]))
        for i in range(len(self.canvas_arr)):
            self.canvas_arr[i] = list(map(lambda x: int(x * self.k), self.canvas_arr[i]))
        self.center = list(map(lambda x: int(x * self.k), self.center))

        if DEBUG:
            print(f'\n{self.scaling.__name__}:\t self.center: {self.center}\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')

    def on_focus(self):
        minusx = min([i[0] for i in self.canvas_rect.values()] + [i[0] for i in self.canvas_arr]) - self.frame_size
        minusy = min([i[1] for i in self.canvas_rect.values()] + [i[1] for i in self.canvas_arr]) - self.frame_size
        for k in self.canvas_rect.keys():
            self.canvas_rect[k][0] -= minusx
            self.canvas_rect[k][1] -= minusy
        for i in range(len(self.canvas_arr)):
            self.canvas_arr[i][0] -= minusx
            self.canvas_arr[i][1] -= minusy
        self.center[0] -= minusx
        self.center[1] -= minusy

        if DEBUG:
            print(f'\n{self.on_focus.__name__}:\t '
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')

    # переворачиваем ось Y вниз, как в экранную систему координат
    # после масштабирования!!!!!
    def reverse_y(self):
        for k in self.canvas_rect.keys():
            self.canvas_rect[k][1] = self.real_y - self.frame_size - self.canvas_rect[k][1]
        for i in range(len(self.canvas_arr)):
            self.canvas_arr[i][1] = self.real_y - self.frame_size - self.canvas_arr[i][1]
        self.center[1] = self.real_y - self.frame_size - self.center[1]

        if DEBUG:
            print(f'\n{self.reverse_y.__name__}:\t self.center: {self.center}\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')

    def add_frame(self):
        for k in self.canvas_rect.keys():
            self.canvas_rect[k][0] += self.frame_size
            self.canvas_rect[k][1] += self.frame_size
        for i in range(len(self.canvas_arr)):
            self.canvas_arr[i][0] += self.frame_size
            self.canvas_arr[i][1] += self.frame_size
        self.center[0] += self.frame_size
        self.center[1] += self.frame_size
        if DEBUG:
            print(f'\n{self.add_frame.__name__}:\t self.center: {self.center}\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')

    def set_data(self, rect, arr):
        if len(rect) + len(arr) == 0:
            return
        self.rectp = rect
        self.arrp = arr
        for k in self.rectp.keys():
            self.canvas_rect[k] = list(self.rectp[k])
        self.canvas_arr = list()
        for i in range(len(self.arrp)):
            self.canvas_arr.append(list(self.arrp[i]))

        if DEBUG:
            print(f'START {self.set_data.__name__}:\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}')
        self.update_sup_data()
        self.update_koef()

        self.to_positiv_coords()
        self.scaling()
        self.on_focus()
        self.reverse_y()
        self.add_frame()

        if DEBUG:
            print(f'END {self.set_data.__name__}:\t self.center: {self.center}\n'
                  f'self.canvas_rect: {self.canvas_rect}\n'
                  f'self.canvas_arr: {self.canvas_arr}\n' + '-' * 100)
        self.update()

    # оси координат
    def paint_axis(self, qp):
        pen = QPen()
        pen.setWidth(1)
        pen.setColor(Qt.black)
        qp.setPen(pen)

        x, y = self.center
        qp.drawLine(x, 0, x, self.height())
        qp.drawLine(0, y, self.width(), y)

    def paint_rect(self, qp):
        pen = QPen()
        pen.setWidth(5)
        pen.setColor(Qt.red)
        qp.setPen(pen)
        if len(self.rectp) == 1:
            qp.drawPoint(*list(self.canvas_rect.values())[0])
        elif len(self.rectp) == 2:
            p1, p2 = list(self.canvas_rect.values())
            qp.drawLine(*p1, *p2)
        elif len(self.rectp) == 3:
            p1, p2, p3 = list(self.rectp.values())
            c1, c2, c3 = list(self.canvas_rect.values())
            if if_90_grad(p1, p2, p3):
                qp.drawLine(*c1, *c2)
                qp.drawLine(*c3, *c2)
            elif if_90_grad(p1, p3, p2):
                qp.drawLine(*c1, *c3)
                qp.drawLine(*c3, *c2)
            elif if_90_grad(p2, p1, p3):
                qp.drawLine(*c1, *c3)
                qp.drawLine(*c1, *c2)
        elif len(self.rectp) == 4:
            p1, p2, p3, p4 = list(self.rectp.values())
            c1, c2, c3, c4 = list(self.canvas_rect.values())
            if if_90_grad(p1, p2, p3):
                qp.drawPolygon(*map(lambda x: QPoint(*x), [c1, c2, c3, c4]))
            elif if_90_grad(p1, p3, p2):
                qp.drawPolygon(*map(lambda x: QPoint(*x), [c1, c3, c2, c4]))
            elif if_90_grad(p2, p1, p3):
                qp.drawPolygon(*map(lambda x: QPoint(*x), [c2, c1, c3, c4]))

    def paint_points(self, qp):
        pen = QPen()
        pen.setWidth(10)
        pen.setColor(Qt.blue)
        qp.setPen(pen)

        for i in range(len(self.canvas_arr)):
            qp.drawPoint(*self.canvas_arr[i])

    def paint_text(self, qp):
        pen = QPen()
        pen.setWidth(1)
        pen.setColor(Qt.black)
        qp.setPen(pen)

        font = QFont()
        font.setPixelSize(self.text_height)
        qp.setFont(font)
        for k in self.rectp.keys():
            text = f'{k}{self.rectp[k]}'
            x, y = self.canvas_rect[k]
            qp.drawText(x + 5, y - 5, text)
            # qp.drawText(x + 5, y - self.text_height - 5, self.text_width, self.text_height, Qt.TextWordWrap, text)
        for i in range(len(self.arrp)):
            text = f'{self.arrp[i]}'
            x, y = self.canvas_arr[i]
            qp.drawText(x + 5, y - 5, text)

    def paintEvent(self, event):
        qp = QPainter(self)
        qp.begin(self)

        # делаем белый фон
        qp.setBrush(Qt.white)
        qp.drawRect(self.rect())
        #

        # оси координат
        self.paint_axis(qp)
        # прямоугольник
        self.paint_rect(qp)
        # точки
        self.paint_points(qp)
        # текст
        self.paint_text(qp)

        # qp.setPen(Qt.red)
        # print('height: ', self.height())
        # qp.drawLine(0, self.height() - 1, self.width(), self.height() - 1) # абсцисса
        # qp.drawLine(0, self.height() - 1, 0, 0) # орбината

        qp.end()


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('main_window.ui', self)
        self.setGeometry(500, 100, 2000, 1500)

        # холст
        self.canvas = CanvasWidget()
        self.stackedWidget.addWidget(self.canvas)
        self.stackedWidget.setCurrentWidget(self.canvas)
        ##

        # словарь и масссив точек
        self.rect = dict() # {a: (x, y), b: (x, y), c: (x, y)}
        self.arrp = list()
        ##

        # кнопки
        self.add_pa_pbtn.clicked.connect(self.add_pa)
        self.add_pb_pbtn.clicked.connect(self.add_pb)
        self.add_pc_pbtn.clicked.connect(self.add_pc)
        self.add_pd_pbtn.clicked.connect(self.add_pd)
        self.del_all_points_rect_pbtn.clicked.connect(self.del_all_points_rect)
        self.del_point_rect_pbtn.clicked.connect(self.del_point_rect)
        self.edit_point_rect_pbtn.clicked.connect(self.edit_point_rect)

        self.add_point_arr_pbtn.clicked.connect(self.add_point_arr)
        self.del_all_points_arr_pbtn.clicked.connect(self.del_all_points_arr)
        self.edit_point_arr_pbtn.clicked.connect(self.edit_point_arr)
        self.del_point_arr_pbtn.clicked.connect(self.del_point_arr)

        self.spinBox_x.valueChanged.connect(self.clean_status_bar)
        self.spinBox_y.valueChanged.connect(self.clean_status_bar)
        self.edit_point_rect_cb.currentIndexChanged.connect(self.clean_status_bar)

        self.paint_res_pbtn.clicked.connect(self.paint_res)
        ##

        # таблицы
        self.table_rect.setColumnCount(3)
        self.table_rect.setHorizontalHeaderLabels(['id', 'X', 'Y'])
        ##

    def add_point_rect_to_data(self, id, x, y):
        self.rect[id] = (x, y)
        self.del_point_rect_cb.addItem(id)
        self.edit_point_rect_cb.addItem(id)

        numrow = self.table_rect.rowCount()
        self.table_rect.setRowCount(numrow + 1)

        for i, data in enumerate([id, x, y]):
            self.table_rect.setItem(numrow, i, QTableWidgetItem(str(data)))

    def check_and_add_point_rect(self, id):
        self.clean_status_bar()
        x = self.spinBox_x.value()
        y = self.spinBox_y.value()

        if self.rect.get(id) is None:
            if len(self.rect) == 0:
                self.add_point_rect_to_data(id, x, y)
            elif len(self.rect) == 1:
                if list(self.rect.values())[0] == (x, y):
                    self.statusbar.showMessage(ERR_NOT_RECT)
                else:
                    self.add_point_rect_to_data(id, x, y)
            else:
                p1, p2 = self.rect.values()  # координаты двух имеющихся точек
                p3 = (x, y)

                if p1 == (x, y) or p2 == (x, y):
                    self.statusbar.showMessage(ERR_NOT_RECT)
                    return

                if if_90_grad(p2, p1, p3):
                    x4 = x + (p2[0] - p1[0])
                    y4 = y + (p2[1] - p1[1])
                elif if_90_grad(p1, p2, p3):
                    x4 = p1[0] + (x - p2[0])
                    y4 = p1[1] + (y - p2[1])
                elif if_90_grad(p1, p3, p2):
                    x4 = p1[0] + (p2[0] - x)
                    y4 = p1[1] + (p2[1] - y)
                else:
                    self.statusbar.showMessage(ERR_NOT_RECT)
                    return
                # # находим вектора
                # v12 = (p1[0] - p2[0], p1[1] - p2[1])
                # v13 = (p1[0] - x, p1[1] - y)
                # v32 = (x - p2[0], y - p2[1])
                #
                # # проверяем перпендикулярность углов 213 и 123 и 132 по скалярному произведению
                # # высчитываем 4 точку
                # if v12[0] * v13[0] + v12[1] * v13[1] == 0:
                #     x4 = x + (p2[0] - p1[0])
                #     y4 = y + (p2[1] - p1[1])
                # elif v12[0] * v32[0] + v12[1] * v32[1] == 0:
                #     x4 = p1[0] + (x - p2[0])
                #     y4 = p1[1] + (y - p2[1])
                # elif v13[0] * v32[0] + v13[1] * v32[1] == 0:
                #     x4 = p1[0] + (p2[0] - x)
                #     y4 = p1[1] + (p2[1] - y)
                # else:
                #     self.statusbar.showMessage(ERR_NOT_RECT)
                #     return

                self.add_point_rect_to_data(id, x, y)
                id4 = 'ABCD'
                for i in self.rect.keys():
                    id4 = id4.replace(i, '')
                self.add_point_rect_to_data(id4, x4, y4)
        else:
            self.statusbar.showMessage(ERR_RECT_EXIST_POINT)

        if DEBUG:
            print(f'{self.check_and_add_point_rect.__name__}:\t self.rect: {self.rect}')

    def add_pa(self):
        self.check_and_add_point_rect('A')

    def add_pb(self):
        self.check_and_add_point_rect('B')

    def add_pc(self):
        self.check_and_add_point_rect('C')

    def add_pd(self):
        self.check_and_add_point_rect('D')

    def del_all_points_rect(self):
        self.clean_status_bar()

        self.rect = dict()
        self.table_rect.setRowCount(0)
        self.edit_point_rect_cb.clear()
        self.del_point_rect_cb.clear()
        if DEBUG:
            print(f'{self.del_all_points_rect.__name__}:\t\t self.rect: {self.rect}')

    def del_point_rect(self):
        self.clean_status_bar()

        id = self.del_point_rect_cb.currentText()
        if id != '':
            # удаляем из таблицы
            for i in range(len(self.rect.keys())):
                if self.table_rect.item(i, 0).text() == id:
                    self.table_rect.removeRow(i)
                    break

            # удаляем из выпадающего списка
            for i in range(len(self.rect.keys())):
                if self.del_point_rect_cb.itemText(i) == id:
                    self.del_point_rect_cb.removeItem(i)
                    break
            for i in range(len(self.rect.keys())):
                if self.edit_point_rect_cb.itemText(i) == id:
                    self.edit_point_rect_cb.removeItem(i)
                    break

            # удаляем из словаря
            del self.rect[id]

            if DEBUG:
                print(f'{self.del_point_rect.__name__}:\t self.rect: {self.rect}')

    def edit_point_rect(self):
        self.clean_status_bar()

        if len(self.rect.keys()) == 0 or len(self.rect.keys()) == 4:
            self.statusbar.showMessage(ERR_EDIT_RECT_POINT)
        else:
            id = self.edit_point_rect_cb.currentText()
            x = self.spinBox_x.value()
            y = self.spinBox_y.value()

            for i in self.rect.keys():
                if i != id and x == self.rect[i][0] and y == self.rect[i][1]:
                    self.statusbar.showMessage(ERR_NOT_RECT)
                    return

            # изменяем в таблице
            for i in range(len(self.rect.keys())):
                if self.table_rect.item(i, 0).text() == id:
                    self.table_rect.setItem(i, 1, QTableWidgetItem(str(x)))
                    self.table_rect.setItem(i, 2, QTableWidgetItem(str(y)))
            # изменяем в словаре
            self.rect[id] = (x, y)

        if DEBUG:
            print(f'{self.check_and_add_point_rect.__name__}:\t self.rect: {self.rect}')

    def add_point_arr(self):
        self.clean_status_bar()
        x = self.spinBox_x.value()
        y = self.spinBox_y.value()

        self.arrp.append((x, y))
        id = 'p' + str(len(self.arrp))
        self.del_point_arr_cb.addItem(id)
        self.edit_point_arr_cb.addItem(id)

        numrow = self.table_arr.rowCount()
        self.table_arr.setRowCount(numrow + 1)

        for i, data in enumerate([id, x, y]):
            self.table_arr.setItem(numrow, i, QTableWidgetItem(str(data)))

        if DEBUG:
            print(f'{self.add_point_arr.__name__}:\t\t self.arrp: {self.arrp}')

    def del_all_points_arr(self):
        self.clean_status_bar()
        self.arrp = list()
        self.table_arr.setRowCount(0)
        self.edit_point_arr_cb.clear()
        self.del_point_arr_cb.clear()

        if DEBUG:
            print(f'{self.del_all_points_arr.__name__}:\t self.arrp: {self.arrp}')

    def edit_point_arr(self):
        self.clean_status_bar()

        id = int(self.edit_point_arr_cb.currentText()[1:])
        x = self.spinBox_x.value()
        y = self.spinBox_y.value()
        self.arrp[id - 1] = (x, y)

        # изменяем в таблице
        for i in range(len(self.arrp)):
            if self.table_arr.item(i, 0).text() == f'p{id}':
                self.table_arr.setItem(i, 1, QTableWidgetItem(str(x)))
                self.table_arr.setItem(i, 2, QTableWidgetItem(str(y)))

        if DEBUG:
            print(f'{self.edit_point_arr.__name__}:\t\t self.arrp: {self.arrp}')

    def del_point_arr(self):
        self.clean_status_bar()

        id = self.del_point_arr_cb.currentText()
        if id != '':
            idi = int(id[1:]) - 1
            # удаляем из таблицы
            self.table_arr.removeRow(idi)
            for i in range(idi, len(self.arrp)):
                self.table_arr.setItem(i, 0, QTableWidgetItem('p' + str(i + 1)))

            # удаляем из выпадающего списка
            self.del_point_arr_cb.removeItem(idi)
            for i in range(idi, len(self.arrp)):
                self.del_point_arr_cb.setItemText(i, 'p' + str(i + 1))

            self.edit_point_arr_cb.removeItem(idi)
            for i in range(idi, len(self.arrp)):
                self.edit_point_arr_cb.setItemText(i, 'p' + str(i + 1))

            # удаляем из массива
            del self.arrp[idi]

            if DEBUG:
                print(f'{self.del_point_arr.__name__}:\t\t self.arrp: {self.arrp}')

    def clean_status_bar(self):
        self.statusbar.clearMessage()

    def paint_res(self):

        self.rect = {
            'A': (6, 0),
            'C': (7, 3),
            'D': (1, 5),
            'B': (0, 2)
        }
        self.arrp = [(20, 30), (10, 10), (19, 10), (10, 5)]

        if len(self.rect) == 0 and len(self.arrp) == 0:
            self.statusbar.showMessage(ERR_NO_DATA)
        else:
            self.canvas.set_data(self.rect, self.arrp)
            self.canvas.update()


def exept_hooks(cls, exeption, trades):
    sys.__excepthook__(cls, exeption, trades)


if __name__ == '__main__':
    sys.excepthook = exept_hooks
    app = QApplication(sys.argv)
    main = MainWindow()
    main.show()
    sys.exit(app.exec())
