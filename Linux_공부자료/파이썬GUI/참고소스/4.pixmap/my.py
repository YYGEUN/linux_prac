import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수
from PyQt5.QtGui import QPixmap
from PyQt5.QtGui import *
from PyQt5.QtCore import *
        
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("pixmap.ui", self)
        self.pixmap = QPixmap('back.png')
        self.pixmap = self.pixmap.scaledToWidth(300)
                
        self.rotatevalue = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update)
        self.timer.start(100) # Only one timer is needed

    def signalSet(self):        
        self.ui.pushButton.clicked.connect(self.exitbtn)
        
    def paintEvent(self, event):
        print("paintEvent", event)
        self.rotatevalue+=1
        qp = QPainter()
        qp.begin(self)
        qp.drawPixmap(0, 0, self.pixmap)

        qp.setPen(QPen(QColor(255, 0, 0), 3))        
        qp.drawLine(QPoint(100, 100), QPoint(200, 100)) 
        qp.save()
        qp.setPen(QPen(QColor(0, 255, 0), 3))  
        qp.translate(150, 150)
        qp.rotate(0)
        qp.drawLine(QPoint(0, 0), QPoint(100, 0)) 
        qp.restore()
        qp.save()
        qp.setPen(QPen(QColor(0, 0, 255), 3)) 
        qp.translate(150, 150)
        qp.rotate(self.rotatevalue)
        qp.drawLine(QPoint(0, 0), QPoint(100, 0)) 
        qp.restore()
        qp.end()

        
    def showForm(self):
        self.ui.show()
        print("show")
        
    def exitbtn(self):
        print(self.sender().text(), self.sender().objectName())
        if self.ui.checkBox.isChecked() == True:
            print("checked")            
        else:
            print("unchecked")
            
            QtWidgets.QMessageBox.about(self,'Title','About Message')
            reply = QtWidgets.QMessageBox.question(self,
                                    'Message', 'Are you sure to quit?',
                                    QtWidgets.QMessageBox.Yes |
                                    QtWidgets.QMessageBox.No,
                                    QtWidgets.QMessageBox.No)            
            print(reply == QtWidgets.QMessageBox.Yes)
            if reply == QtWidgets.QMessageBox.No :
                return
            
        self.ui.close()

if __name__ == '__main__':
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
    print("종료")
