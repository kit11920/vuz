import sys
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QFileDialog

from lib import Libarr_ctypes, Libarr_ExtModule
import design, path_libarr_design, type_c_py_lib

# Класс рабочего окна на котором производится работа с массивом
class WorkWindow(QMainWindow, design.Ui_MainWindow):
    def __init__(self, lib):
        super().__init__()
        # uic.loadUi('./py/design.ui', self)
        self.setupUi(self) # Загружаем дизайн
        self.lib = lib

        self.shift_btn.clicked.connect(self.shift_arr)
        self.input_arr_lineEdit.textChanged.connect(self.clear_error)
        self.filter_btn.clicked.connect(self.filter_arr)

    # Операция сдвига массива на k
    def shift_arr(self):
        arr = self.input_arr()
        if arr == []:
            return

        k = self.k_spinBox.value()

        rc, arr = self.lib.k_shift_arr(arr, k)
        if rc != 0:
            self.error_output.setText('ERROR: ошибка в функции k_shift_arr')
            return
        
        self.shifted_arr_lineEdit.setText(' '.join(map(str, arr)))

    # Фильтрация массива по полному квадрату
    def filter_arr(self):
        arr = self.input_arr()
        if arr == []:
            return

        # Выбор способа выделения памяти
        if self.economy_mem_rbtn.isChecked():
            print('---Экономичное выделение памяти---')
            rc, arr = self.lib.make_sqrt_arr_eco(arr)
        else:
            print('---Выделение памяти с запасом---')
            rc, arr = self.lib.make_sqrt_arr_reserv(arr)
        
        if rc < 0:
            self.error_output.setText('ERROR: ошибка в функции make_sqrt_arr_eco')
            return
        
        if arr == []:
            self.filtered_arr_lineEdit.setText('-')    
        else:
            self.filtered_arr_lineEdit.setText(' '.join(map(str, arr)))
    
    # Вводит массив 
    def input_arr(self):
        arr = self.input_arr_lineEdit.text()
        if arr == '':
            self.error_output.setText('ERROR: введите массив целых чисел')
            return []
        
        try:
            arr = list(map(int, arr.split()))
        except Exception as err:
            # print(err)
            # print('\n\n')
            self.error_output.setText('ERROR: ошибка ввода')
            return []
        
        return arr

    # Очищает строку ошибок когда изменяется содердимое окна ввода
    def clear_error(self):
        self.error_output.setText('')

# Класс выбора пути до библиотеки libarr.so
class ChosePathLibWindow(QWidget, path_libarr_design.Ui_Form):
    def __init__(self, libname):
        super().__init__()
        # uic.loadUi('./py/path_libarr_design.ui', self)
        self.setupUi(self) # Загружаем дизайн

        self.libname = libname
        self.path_lineEdit.setText(libname)
        self.choose_path_btn.clicked.connect(self.choose_path)
        self.path_lineEdit.textChanged.connect(self.write_path)
        self.done_btn.clicked.connect(self.out)

    # Открывает окно выбора пути до файла
    def choose_path(self):
        fileName = QFileDialog.getOpenFileName(self, "Open File", ".",
                                       "Libraries (*.so)")[0]
        self.path_lineEdit.setText(fileName)
        self.libname = fileName
    
    # Записывает введенный пользователем путь в переменную пути (когда окно ввода пути изменилось)
    def write_path(self):
        self.libname = self.path_lineEdit.text()

    # Реагирует на кнопку "Готово" 
    # и если путь до библиотеки выбран верно открывает основное рабочее окно
    def out(self):
        try:
            libarr = Libarr_ctypes(self.libname)
            self.hide()
            self.main = WorkWindow(libarr)
            self.main.show()

        except OSError:
            self.error_output.setText('Error library')
            self.show()
            return
        except AttributeError:
            self.error_output.setText('Error library')
            self.show()
            return

# Класс выбора способа подключения библиотеки на Си к скрипту на питоне
class Choose_type_lib_c_py(QWidget, type_c_py_lib.Ui_Form):
    def __init__(self):
        super().__init__()
        # uic.loadUi('./py/type_c_py_lib.ui', self)
        self.setupUi(self) # Загружаем дизайн

        self.done_btn.clicked.connect(self.out)
    
    # Открывается следующее окно в зависмимости от выбора
    def out(self):
        if self.ctypes_rbtn.isChecked():
            print('---Используется ctypes---')
            self.hide()
            libarr_name = './libarr.so'
            self.choose = ChosePathLibWindow(libarr_name)
            self.choose.show()
        else:
            print('---Используется модуль расширения---')
            self.hide()
            libarr = Libarr_ExtModule()
            self.main = WorkWindow(libarr)
            self.main.show()


# Уточняет описание ошибки программы (для программиста)
def exept_hooks(cls, exeption, trades):
    sys.__excepthook__(cls, exeption, trades)


if __name__ == '__main__':
    sys.excepthook = exept_hooks
    app = QApplication(sys.argv)

    window = Choose_type_lib_c_py()
    window.show()

    
    sys.exit(app.exec())



# pyuic5 info.ui -o info.py

