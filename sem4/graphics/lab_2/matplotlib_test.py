import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QMenu, QVBoxLayout, QSizePolicy, QMessageBox, QWidget, QPushButton
from PyQt5.QtGui import QIcon
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
import random
import numpy as np
import math as m

class App(QMainWindow):

    def __init__(self):
        super().__init__()
        self.left = 10
        self.top = 10
        self.title = 'PyQt5 and Matplotlib Integration - pythonspot.com'
        self.width = 640
        self.height = 400
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left + 100, self.top + 100, self.width, self.height)
        m = PlotCanvas(self, width=5, height=4)
        m.move(0,0)
        button = QPushButton('Sample PyQt5 Button', self)
        button.setToolTip('This is an illustrative button')
        button.move(500,0)
        button.resize(140,100)
        self.show()

class PlotCanvas(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)
        FigureCanvas.__init__(self, fig)
        self.setParent(parent)
        FigureCanvas.setSizePolicy(self, QSizePolicy.Expanding, QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self.plot()

    def plot(self):
        # data = [random.random() for i in range(25)]
        ax = self.figure.add_subplot(111)
        ax.set_title('График функции')
        ax.set_xlabel('x')
        ax.set_ylabel('y')


        # x = np.arange(0, 10, 0.1)
        # # plotting the lines
        # a1 = 4 - 2 * x
        # # a = b = r = 1
        # a1 = plt.Circle((0, 0), 0.2, color='r')
        # print(a1)
        # # a2 = 3 - 0.5 * x
        # a3 = 1 - x
        # a3 = 1 / x


        data = np.linspace(0, 2 * np.pi, 150)
        radius = 0.6
        a1 = radius * np.cos(data)
        # print(a1)
        # x = np.arange(0, 10, 0.1)
        # a3 = 1 / x


        a = radius * np.cos(data)
        # b = radius * np.sin(data)

        # Plot

        ax.plot(a)
        # a4 = np.minimum(a1, a2)

        # ax.plot(a1)
        # ax.plot(x, a3)

        # ax.fill_between(x, a1, a3, color='green',
        #                  alpha=0.5)


        # Вывод графика
        # ax.plot(x, y)
        # ax.plot(data, 'r-')
        # ax.set_title('PyQt and Matplotlib Demonstration')
        self.draw()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())