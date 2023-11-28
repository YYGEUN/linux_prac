import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수
import os

print(os.getcwd())
  
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi(os.getcwd() + "\\1.btn_label\\form.ui", self)

    def signalSet(self):        
        self.ui.pushButton1.clicked.connect(self.button1Function)
        self.ui.lineEdit.textChanged.connect(self.textChangedlineEdit)
        #self.ui.lineEdit.returnPressed.connect(self.returnCheck)

        #self.ui.lineEdit.textChanged.connect(self.ui.label.setText)
        
    def showForm(self):
        self.ui.show()
        print("show")
        
    def button1Function(self):
        print("btn1 clicked")
        self.ui.label.setText("첫번째 버튼")

    def textChangedlineEdit(self, string):
        print("lineEdit textchanged", string)
        #self.ui.label.setText(self.ui.lineEdit.text())

    #두번째/세번째 버튼과 lineedit의 returnpressed이벤트를 이용하여 엔터 입력시
    #라벨에 글자 출력
        

    #def returnCheck(self):
    #    self.ui.label.setText(self.ui.lineEdit.text())
        
  
if __name__ == '__main__':
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
