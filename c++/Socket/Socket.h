#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/un.h>
#include <sys/in.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

class SocketServer(){
private:
	int serverFd;
	struct sockaddr_un unAddr;
	struct sockaddr_in inAddr;

	std::vector<int> clientsFd;
	int clientsCount;
	std::vector<struct sockaddr> clientsAddr;
	std::vecotr<int> clientsAddrLen;

public:
	SocketServer(const char* type = "TCP");
	SocketServer(int domain,int type,int protocol=0);
	void setAddr(const char* fileName);
	void setAddr(const char* ip,unsigned short int port);
	bool accept(int vol=5,bool block = true);
	int getClientsCount();
	struct sockaddr getClientAddr(int idx);
	void clearClient(int idx=-1);
	
	void setBlock(bool on,int clientIdx=0);

	int readSock(char* buffer, int len,int clientIdx=0);
	int readSock(std::string &buffer, int len=100,int clientIdx=0);
	int readline(char* buffer,int len,char eol='\n',int clientIdx=0);
	int readline(std::string &buffer,int len=100,char eol='\n',int clientIdx=0);
	
	int writeSock(const char* buffer,int len,int clientIdx=0);
	int writeSock(const std::string &buffer,int clientIdx = 0);


private:
};

class SocketClient(){
};


#endif
