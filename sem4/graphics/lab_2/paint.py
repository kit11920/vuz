from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QPen, QFont
from PyQt5.QtCore import Qt, QPoint
import math as m

DEBUG = True



class CanvasWidget(QWidget):
    def __init__(self):
        super().__init__()

        self.c = 1e5
        self.a = self.b = self.r = 100

        self.real_x = self.width()
        self.real_y = self.height()
        self.c = min(self.real_x, self.real_y) ** 2
        self.a = self.b = int(m.sqrt(self.c))
        self.r = min(self.real_x, self.real_y) // 2

    def circle(self, x):
        self.a = self.b = m.sqrt(self.c)
        yp = m.sqrt(self.r ** 2 - (x - self.a) ** 2) + self.b
        ym = - m.sqrt(self.r ** 2 - (x - self.a) ** 2) + self.b
        return yp, ym

    def hyperbole(self, x):
        # return - self.c / x + self.height()
        return self.c / x


    def paintEvent(self, event):
        qp = QPainter(self)
        qp.begin(self)

        # делаем белый фон
        qp.setBrush(Qt.white)
        qp.drawRect(self.rect())
        #

        # центр экрана
        pen = QPen()
        pen.setWidth(5)
        pen.setColor(Qt.green)
        qp.setPen(pen)

        qp.drawLine(self.width() // 2 - 10, self.height() // 2, self.width() // 2 + 10, self.height() // 2)
        qp.drawLine(self.width() // 2, self.height() // 2 - 10, self.width() // 2, self.height() // 2 + 10)
        ##

        pen = QPen()
        pen.setWidth(5)
        pen.setColor(Qt.blue)
        qp.setPen(pen)

        qp.drawEllipse(self.a - self.r, self.b - self.r, self.r * 2, self.r * 2)
        qp.drawPolyline(list(map(lambda x: QPoint(x, round(self.hyperbole(x))), range(1, self.width()))))


        qp.end()