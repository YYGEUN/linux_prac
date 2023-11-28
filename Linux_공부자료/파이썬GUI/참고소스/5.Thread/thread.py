import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수
from PyQt5.QtGui import *
from PyQt5.QtCore import *

import threading, time

def ThreadFunc(form):
    value = 0

    while True:
        value += 1
        form.changeValue(value)
        time.sleep(0.1)
    
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("thread.ui", self)

    def signalSet(self):        
        pass
    
    def changeValue(self, value):        
        self.ui.dial.setValue(value)

    def showForm(self):
        self.ui.show()
        print("show")

if __name__ == '__main__':
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    
    t1 = threading.Thread(target=ThreadFunc, args=(myWindow,))
    t1.start()

    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
    print("종료")
