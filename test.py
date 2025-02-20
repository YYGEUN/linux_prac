import sys
from PyQt5 import QtWidgets #위젯들을 포함하는 클래스 
from PyQt5 import uic     # ui파일을 사용하기 위한 함수
from PyQt5.QtGui import QPixmap
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtCore import QThread, QObject, pyqtSignal
import threading, time
import socket #socket module

BUFFER_SIZE = 1024

maxSpeed = 230
accValue = 3
brkValue = 3
ntValue = 1

portnum = 5005
portchar = 5006

doExit = False
doAcc = False
doBrk = False
curSpeed = 0

client_socket = None

sockMode = True

def client(form):
    # HOST = '192.168.50.31' # loopback
    HOST = '172.30.1.93'
    PORT = portnum
    global client_socket
    
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    bConnected = False
    while doExit == False:
        try:
            print("접속 시도")
            client_socket.connect((HOST, PORT))
            bConnected = True
            break
        except:
            print("exception socket.error")

    if bConnected == False:
        print("접속 실패 TH2 종료")
        return
    else:
        print("접속 완료")
        
    
    form.setMsg("server 접속 완료", True)

    # msg = "conn_ui\x00"
    # client_socket.send(msg.encode())
    
    while doExit == False:
        try:
            data = client_socket.recv(6)
            speed = data.decode()         

            # print(data, speed, int(speed))
            form.setSpeedTarget(int(speed))
        except:
            print("except socket")
            break

            
    client_socket.close()
    print("TH2 종료")

def client2(form):
    # HOST = '192.168.50.31' # loopback
    HOST = '172.30.1.93'
    PORT = portnum
    global client_socket2
    
    client_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    bConnected = False
    while doExit == False:
        try:
            print("접속 시도2")
            client_socket2.connect((HOST, PORT))
            bConnected = True
            break
        except:
            print("exception socket.error2")

    if bConnected == False:
        print("접속 실패 TH2-2 종료")
        return
    else:
        print("접속 완료2")
        
    
    form.setMsg("server 접속 완료2", True)

    # msg = "conn_ui\x00"
    # client_socket.send(msg.encode())
    
    while doExit == False:
        try: 
            data2 = client_socket2.recv(8)
            state = data2.decode()

            # 속도상태 수신
            if state == "speedok0" or state == "speed000" or state == "speedng0": 
              print(state)
              form.setspeedstate(state)

            # 시그널상태 수신
            elif state == "right000" or state == "left0000" or state == "right111" or state == "left1111": 
              print(state)
              form.setsignalstate(state)
            
            # 연료충전 상태 수신
            elif state == "fuel0000":
              print(state)
              form.setfuelstate(state)

            # 연료량 수신
            else:
              print(int(state),state)
              form.setfuelstate(state)

        except:
            print("except socket2")
            break
            
    client_socket2.close()
    print("TH2-2 종료")

class Worker(QThread):
    start_timer_signal = pyqtSignal(str)
    stop_timer_signal = pyqtSignal(str)
    set_fuel_bar_signal = pyqtSignal(str)

    def setsignalstate(self, state):
        if state == "left0000":
            self.start_timer_signal.emit("left")
        elif state == "left1111":
            self.stop_timer_signal.emit("leftoff")
        elif state == "right000":
            self.start_timer_signal.emit("right")
        elif state == "right111":
            self.stop_timer_signal.emit("rightoff")

    def setfuelstate(self, state):
        if state == "fuel0000":
            self.set_fuel_bar_signal.emit("charge")
        else:
            print(state)
            self.set_fuel_bar_signal.emit(state)

    
class Form(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = uic.loadUi("cluster.ui", self)
        self.pixmap = QPixmap('back.png')
        self.pixmap = self.pixmap.scaledToWidth(300)
        self.right = QPixmap('right.PNG')
        self.right = self.right.scaledToWidth(50)
        self.left = QPixmap('left.png')
        self.left = self.left.scaledToWidth(50)
                
        self.rotatevalue = 0
        self.rotatetarget = 0
        self.timerPaint = QTimer(self)
        self.timerPaint.timeout.connect(self.update)
        self.timerPaint.start(30) # Only one timer is needed

        self.timerCalc = QTimer(self)
        self.timerCalc.timeout.connect(self.calcRotate)
        self.timerCalc.start(30) # Only one timer is needed

        self.timerleft = QTimer(self)
        self.timerleft.timeout.connect(self.toggle_image_visibility)
        self.timerleft_started = False
        self.left_visible = False  # 'left.png' 이미지 표시 상태

        self.timerright = QTimer(self)
        self.timerright.timeout.connect(self.toggle_image_visibility)
        self.timerright_started = False
        self.right_visible = False  # 'right.PNG' 이미지 표시 상태

        self.worker_thread = QThread()
        self.worker = Worker()
        self.worker.moveToThread(self.worker_thread)

        self.worker.start_timer_signal.connect(self.start_timer)
        self.worker.stop_timer_signal.connect(self.stop_timer)
        self.worker.set_fuel_bar_signal.connect(self.set_fuel_bar)
        
        self.ui.msg.setText("Turn ON 버튼을 눌러주세요.")
        self.ui.accel.setEnabled(False)
        self.ui.brake.setEnabled(False)
        self.ui.lh.setEnabled(False)
        self.ui.rh.setEnabled(False)

    def signalSet(self):        
        self.ui.system.clicked.connect(self.systembtn)
        self.ui.accel.pressed.connect(self.accelp)
        self.ui.accel.released.connect(self.accelr)
        self.ui.brake.pressed.connect(self.brakep)
        self.ui.brake.released.connect(self.braker)
        self.ui.rh.clicked.connect(self.rightside)
        self.ui.lh.clicked.connect(self.leftside)
        self.ui.fuelbtn.clicked.connect(self.fuel_charge)

    def fuel_charge(self):
        msg = "fuel_charge\x00"
        client_socket2.send(msg.encode())

    def rightside(self): ##############################################
        global client_socket2
        if self.sender().isChecked() == True:
            msg = "right_on\x00"
            client_socket.send(msg.encode())
            
        else:
            msg = "right_off\x00"
            client_socket.send(msg.encode())

    def leftside(self):  ##############################################
        global client_socket2
        if self.sender().isChecked() == True:
            msg = "left_on\x00"
            client_socket2.send(msg.encode())
            
        else:
            msg = "left_off\x00"
            client_socket2.send(msg.encode())

    def calcRotate(self):
        if self.rotatevalue < self.rotatetarget:
            self.rotatevalue += 1
        elif self.rotatevalue > self.rotatetarget:
            self.rotatevalue -= 1

        if self.rotatevalue < 0:
            self.rotatevalue = 0
            
        if self.rotatevalue > maxSpeed:
            self.rotatevalue = maxSpeed
            
        self.ui.lcdNumber.display(self.rotatevalue)

    def setSpeedTarget(self, value): #########################################################################################################################
        self.rotatetarget = value
        
    def setspeedstate(self, value): #########################################################################################################################
        if(value == "speedng0"):
            self.ui.msg.setText("속도를 줄이세요")
        elif(value == "speedok0"):
            self.ui.msg.setText("---")
        elif(value == "speed000"):
            self.ui.msg.setText("정지 - 출발가능")

    def setfuelstate(self,state):
        if state == "fuel0000":
            self.worker.setfuelstate("fuel0000")
            self.update()
        elif state == "fuel0001":
            self.worker.setfuelstate("fuel0001")
            self.update()

    def set_fuel_bar(self, signo):
        print(signo)
        if signo == "charge":
            self.ui.fuelbar.setValue(100)
        else:
            self.ui.fuelbar.setValue(int(signo))

    def start_timer(self, signo):
        if signo == "left" and not self.timerleft_started:
            self.timerleft.start(500)  # 'left.png' 이미지를 1초 간격으로 표시/숨기기 시작
            self.timerleft_started = True
        elif signo == "right" and not self.timerright_started:
            self.timerright.start(500)  # 'right.PNG' 이미지를 1초 간격으로 표시/숨기기 시작
            self.timerright_started = True

    def stop_timer(self,signo):
        if signo == "leftoff":
            self.timerleft.stop()
            self.timerleft_started = False
        elif signo == "rightoff":
            self.timerright.stop()
            self.timerright_started = False

    def toggle_image_visibility(self):
        if self.sender() == self.timerleft:
            self.left_visible = not self.left_visible  # 'left.png' 이미지 표시 상태 변경
        elif self.sender() == self.timerright:
            self.right_visible = not self.right_visible  # 'right.PNG' 이미지 표시 상태 변경
        self.update()  # paintEvent를 호출하여 이미지를 다시 그립니다.

    def setsignalstate(self, state):
        if state == "left0000":
            self.worker.setsignalstate("left0000")
            self.left_visible = True
            self.update()
        elif state == "left1111":
            self.worker.setsignalstate("left1111")
            self.left_visible = False
            self.update()
        elif state == "right000":
            self.worker.setsignalstate("right000")
            self.right_visible = True
            self.update()
        elif state == "right111":
            self.worker.setsignalstate("right111")
            self.right_visible = False
            self.update()

    def setMsg(self, value, append):
        if append == True:
            self.ui.msg.setText(self.ui.msg.text() + "," + value)
        else:
            self.ui.msg.setText(value)
        
    def paintEvent(self, event):       
        qp = QPainter()
        qp.begin(self)
        qp.drawPixmap(0, 0, self.pixmap)
        qp.save()        
        qp.setPen(QPen(QColor(0, 0, 255), 3)) 
        qp.translate(150, 150)

        qp.rotate(self.rotatevalue - 200)
        qp.drawLine(QPoint(100, 0), QPoint(0, 0)) 
        qp.restore()

        if self.left_visible == True:
            qp.drawPixmap(30, 240, self.left)
        if self.right_visible == True:
            qp.drawPixmap(220, 240, self.right)

        qp.end()
        
    def showForm(self):
        self.ui.show()
        print("show")
        
    def systembtn(self):
        global client_socket
        print("systembtn clicked")
        if self.sender().isChecked() == True:
            self.ui.msg.setText("운행 시작.")
            self.ui.accel.setEnabled(True)
            self.ui.brake.setEnabled(True)
            self.ui.lh.setEnabled(True)
            self.ui.rh.setEnabled(True)
            msg = "turn_on\x00"
            client_socket.send(msg.encode())
            
        else:
            self.ui.msg.setText("운행 종료.")
            self.ui.accel.setEnabled(False)
            self.ui.brake.setEnabled(False)
            self.ui.lh.setEnabled(False)
            self.ui.rh.setEnabled(False)
            self.rotatetarget = 0
            msg = "turn_off\x00"
            client_socket.send(msg.encode())
        
    def accelp(self):
        print("accel on")
        if sockMode == True:
            msg = "acin\x00"
            client_socket.send(msg.encode())
        else :
            global doAcc
            doAcc = True
        
    def brakep(self):
        print("brake on")
        if sockMode == True:
            msg = "brin\x00"
            client_socket.send(msg.encode())
        else :
            global doBrk
            doBrk = True
        
    def accelr(self):
        print("accel off")
        if sockMode == True:
            msg = "nope\x00"
            client_socket.send(msg.encode())
        else :
            global doAcc
            doAcc = False

    def braker(self):
        print("brake off")
        if sockMode == True:
            msg = "nope\x00"
            client_socket.send(msg.encode())
        else :
            global doBrk
            doBrk = False

if __name__ == '__main__': 
    
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QtWidgets.QApplication(sys.argv) 

    #WindowClass의 인스턴스 생성
    myWindow = Form()
    myWindow.signalSet()
    myWindow.showForm()
    
    # t1 = threading.Thread(target=calcSpeed, args=(myWindow,))
    # t1.start()
    t2 = threading.Thread(target=client, args=(myWindow,))
    t2.start()
    time.sleep(1)
    t3 = threading.Thread(target=client2, args=(myWindow,))
    t3.start()
    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
    print("종료")
    doExit = True
