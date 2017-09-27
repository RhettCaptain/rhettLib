#include "../SerialPort.h"

int main(){
	SerialPort* sp = new SerialPort("/dev/ttyUSB2"); 
	sp->openPort();
	sp->setPort();
}
