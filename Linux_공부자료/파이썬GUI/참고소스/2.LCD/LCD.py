import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수

  
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("lcd.ui", self)
        self.myvalue = 0


        #지역변수로 활용
        pybutton = QtWidgets.QPushButton('동적버튼(10진수)', self)
        pybutton.resize(100, 32)
        pybutton.move(0, 0)
        pybutton.clicked.connect(self.dynamicBtn)
                
        pybutton = QtWidgets.QPushButton('동적버튼(16진수)', self)
        pybutton.resize(100, 32)
        pybutton.move(101, 0)
        pybutton.clicked.connect(self.dynamicBtn2)

    def signalSet(self):        
        self.ui.pushButton.clicked.connect(self.button1Function)
        
    def showForm(self):
        self.ui.show()
        print("show")
        
    def button1Function(self):
        print("btn1 clicked")
        self.myvalue+=1
        self.ui.lcdNumber.display(self.myvalue)

    def dynamicBtn(self):
        print("dynamicBtn clicked")
        print(self.sender().text())
        self.ui.lcdNumber.setDecMode()
        
        
    def dynamicBtn2(self):
        print("dynamicBtn2 clicked")
        self.ui.lcdNumber.setHexMode()

    #매뉴얼을 보고 버튼 두개에 16진수 표현/10진수 표현방식변경 기능을 완료하세요
  
if __name__ == '__main__':
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
