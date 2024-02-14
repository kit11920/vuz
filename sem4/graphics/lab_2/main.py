import sys
from PyQt5 import uic
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QTableWidgetItem)
from paint import CanvasWidget

DEBUG = True

# ERRORS
ERR = 'ERROR: '
##


# class InfoWidget(QWidget):
#     def __init__(self):
#         super().__init__()
#         uic.loadUi('info.ui', self)
#         self.setGeometry(1000, 500, 1000, 800)
#
#         self.ok_pbtn.clicked.connect(self.close_window)
#
#     def close_window(self):
#         self.hide()

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('main_window.ui', self)
        self.setGeometry(500, 100, 2000, 2000 - 700)

        # холст
        self.canvas = CanvasWidget()
        self.stackedWidget.addWidget(self.canvas)
        self.stackedWidget.setCurrentWidget(self.canvas)
        ##

        # кнопки

        ##

        # меню
        # self.info_widget = InfoWidget()
        # self.info_qm.aboutToShow.connect(self.show_info)
        # self.exit_pbtn.aboutToShow.connect(self.exit)
        ##

    def clean_status_bar(self):
        self.statusbar.clearMessage()

    def show_info(self):
        print('show')
        self.info_widget.show()

    def exit(self):
        sys.exit(0)


def exept_hooks(cls, exeption, trades):
    sys.__excepthook__(cls, exeption, trades)


if __name__ == '__main__':
    sys.excepthook = exept_hooks
    app = QApplication(sys.argv)
    main = MainWindow()
    main.show()
    sys.exit(app.exec())
