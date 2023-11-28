import sys
from PyQt5 import QtWidgets #위젯 들을 포함하는 클래스
from PyQt5 import uic #.ui파일을 사용하기 위함 함수를 포함하는 모듈
import os
print(os.getcwd())

class MyForm(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("form.ui")
        #self.ui = uic.loadUi(ow.getcwd() + "form.ui")

    def signalslot(self):
        self.ui.btn1.clicked.connect(self.clickedBtn)

    def clickedBtn(self):
        print("btn1 clicked")

    def uiShow(self):
        self.ui.show()


app = QtWidgets.QApplication(sys.argv)

myWindow = MyForm()
myWindow.signalslot()
myWindow.uiShow()

app.exec_() #이벤트루프
print("end")










        
