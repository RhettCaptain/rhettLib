#include "SerialPort.h"

int main(){
	SerialPort* sp = new SerialPort("/dev/ttyS1"); 
	sp->openPort();
	sp->setPort();
}
