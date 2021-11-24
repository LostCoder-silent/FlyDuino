from top import Ui_MainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
from time import sleep
import serial
import glob



class main(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

    
    
def connect():
    a = serial_ports()    
    try:
        realport = serial.Serial(a[window.spinBox.value()], 9600)
        awer = realport.readline()
        print(awer)
    except Exception as e:
        print(e)
        return
    window.lineEdit_2.setText('started')
    realport.write(b'RTR\r\n')
    print('send')
    window.lineEdit.setText(realport.readline().decode())
    window.progressBar.setValue(1)
    a  = realport.readline()
    window.progressBar.setValue(50)
    b = realport.readline()
    window.progressBar.setValue(100)
    window.lineEdit.setText(a.decode())
    window.lineEdit_2.setText(b.decode())
    


def serial_ports():
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result   
    

app = QtWidgets.QApplication(sys.argv)
window = main()
window.show()
window.progressBar.setValue(0)
window.pushButton.clicked.connect(connect)
app.exec() 

