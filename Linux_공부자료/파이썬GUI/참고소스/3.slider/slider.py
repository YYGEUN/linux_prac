import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수

  
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("slider.ui", self)

    def signalSet(self):        
        self.ui.dial.valueChanged.connect(self.ui.lcdNumber.display)
        self.ui.horizontalSlider.valueChanged.connect(self.sliderfunc)
        self.ui.horizontalSlider.valueChanged.connect(self.ui.progressBar.setValue)
        
    def showForm(self):
        self.ui.show()
        print("show")
        
    def sliderfunc(self, value):
        print(value)
        #self.ui.progressBar.setValue(value)

if __name__ == '__main__':
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
