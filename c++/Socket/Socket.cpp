#include "Socket.h"

SocketServer::SocketServer(const char* type){
	if(strcmp(type,"TCP") == 0){
		serverFd = socket(AF_INET,SOCK_STREAM,0);
	}
	else if(strcmp(type,"UDP") == 0){
		serverFd = socket(AF_INET,SOCK_DGRAM,0);
	}
	else{
		throw("not support type");
	}
	clientsCount = 0;
}

SocketServer::SocketServer(int domain,int type,int protocol){
	serverFd = socket(domain,type,protocol);
	clientsCount = 0;
}

void SocketServer::setAddr(const char* fileName){
	unAddr.sun_family = AF_UNIX;
	strcpy(unAddr.sun_path,fileName);
	int len = sizeof(unAddr);
	bind(serverFd,(struct sockaddr*)&unAddr,len);
}

void SocketServer::setAddr(const char* ip,unsigned short int port){
	inAddr.sin_family = AF_INET;
	inAddr.sin_port = port;
	inAddr.s_addr = inet_addr(ip);
	int len = sizeof(inAddr);
	bind(serverFd,(struct sockaddr*)&inAddr,len);
}

bool SocketServer::accpet(int vol,bool block){
	listen(serverFd,vol);

	int flags = fcntl(serverFd,F_GETFL,0);
	if(block){
		fcntl(serverFd,F_SETFL, ~O_NONBLOCK&flags);
	}
	else{
		fcntl(serverFd,F_SETFL, O_NONBLOCK|flags);
	}
	
	struct sockaddr sa;
	int len;
	int clinetFd = accept(serverFd,&sa,&len);
	if(clientFd == INVALID_SOCKET){
		return false;
	}
	clientCount++;
	clientsFd.push_back(clientFd);
	clientsAddr.push_back(sa);
	clientsAddrLen.push_back(len);
	return true;
}

int SocketServer::getClientsCount(){
	return clientsCount;
}

struct sockaddr SocketServer::getClientAddr(int idx){
	if(idx>=0 && idx< clientsCount){
		return clientsAddr[idx];
	}
	else{
		return NULL;	
	}
}
void SocketServer::clearClient(int idx){
	if(idx<0){
		clientsCount = 0;
		clientsFd.clear();
		clientsAddr.clear();
		clientsAddrLen.clear();
	}
	else{
		if(idx>=0 && idx< clientsCount){
			auto it = clientsFd.begin();
			clientsFd.erase(it);
			it = clientsAddr.begin();
			clientsAddr.erase(it);
			it = clientsAddrLen.begin();
			clinetsAddrLen.erase(it);
			clientsCount--;
		}
		else{
			std::cout << "invalid idx!" << endl;
		}
	}
}

void ServerSocket::setBlock(bool on,int clientIdx){
	int flags = fcntl(clientsFd[clientIdx],F_GETFL,0);
	if(on){
		flags &= ~O_NONBLOCK;
	}
	else{
		flags |= O_NONBLOCK;
	}
	fcntl(clientsFd[clientIdx],F_SETFL,flags);
}

int ServerSocket::readSock(char* buffer,int len, int clientIdx){
	int sock = clientsFd[clientIdx];
	int nBytes = read(sock,buffer,len);
	return nBytes;
}

int ServerSocket::readSock(std::string &buffer,int len,int clientIdx){
	char* cBuffer = new char[len];
	int nBytes = readSock(cBuffer,len,clientIdx);
	if(nBytes == -1){
		delete[] cBuffer;
		return -1;
	}
	else{
		buffer.insert(0,cBuffer,nBytes);
		delete[] cBuffer;
		return nBytes;
	}
}

int ServerSocket::readline(char* buffer, int len, char eol,int clientIdx){
	char ch=' ';
	int idx=0;
	while(ch!=eol){
		if(readSock(&ch,1,clientIdx)>0){
			buffer[idx++] = ch;
		}
		if(idx==len){
			cout << "no eol in len bytes" << endl;
			break;
		}
	}
	return idx;
}

int ServerSocket::readline(std::string &buffer,int len,char eol,int clientIdx){
	char* cBuffer = new char[len];
	int nBytes = readline(cBUffer,len,eol,clientIdx);
	if(nBytes == -1){
		delete[] cBuffer;
		return -1;
	}
	else{
		buffer.insert(0,cBuffer,nBytes);
		delete[] cBuffer;
		return nBytes;
	}
}
