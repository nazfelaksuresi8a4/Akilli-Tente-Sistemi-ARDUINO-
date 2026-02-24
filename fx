import sys
import cv2 as cv
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg   
from PyQt5.QtWidgets import QApplication, QLabel, QWidget, QVBoxLayout
from PyQt5.QtCore import *
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import QTimer

class CameraApp(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Gerçek Zamanlı Kamera")

        self.label = QLabel()
        self.label.setAlignment(Qt.AlignCenter)
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

        # Kamera başlat
        self.cap = cv.VideoCapture(0)
        self.label = QLabel()

        layout.addWidget(self.label)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.mainX)
        self.timer.start(30)
    
    def mainX(self):
        ret,frame = self.cap.read()
        frame = cv.cvtColor(frame,cv.COLOR_BGR2RGB)

        if not ret:
            return

        height,width,channels = frame.shape
        bytePerLine = width * channels 

        qimg = QImage(
            frame.data,
            width,
            height,
            bytePerLine,
            QImage.Format_RGB888
        )

        self.label.setPixmap(QPixmap.fromImage(qimg))


app = QApplication(sys.argv)
window = CameraApp()
window.show()
sys.exit(app.exec())
