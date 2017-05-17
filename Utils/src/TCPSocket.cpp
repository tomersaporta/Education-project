/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: user
 */

#include "TCPSocket.h"

namespace networkingLab {




TCPSocket::~TCPSocket() {
	// TODO Auto-generated destructor stub
}

TCPSocket::TCPSocket(size_t port) {


	socket_fd = socket (AF_INET,SOCK_STREAM ,0);
	if (socket_fd < 0){
			cerr<<"Error opening channel"<<endl;
			close();
	}

	bzero(&this->s_local, sizeof(this->s_local));
	this->s_local.sin_family = AF_INET;
	this->s_local.sin_port = htons(port);
	this->s_local.sin_addr.s_addr = htonl(INADDR_ANY);
	 // Binding the socket with the specific IP+PORT
	if(bind(socket_fd ,(struct sockaddr*)&this->s_local, sizeof(this->s_local))<0){
			cerr<<"Error naming channel"<<endl;
			close();
		}
		cout<<"Server is alive and waiting for socket connection from client."<<endl;

}

TCPSocket::TCPSocket(string peerIp, size_t port) {

	socket_fd =socket(AF_INET, SOCK_STREAM,0);
	if(socket_fd <0){
		cerr<<"Error opening channel"<<endl;
		close();
	}
	bzero(&this->s_remote, sizeof(this->s_remote));
		this->s_remote.sin_family = AF_INET;
		this->s_remote.sin_port = htons(port);
		this->s_remote.sin_addr.s_addr =inet_addr(peerIp.c_str());

	//connect the socket to the server
	if(connect(socket_fd, (struct sockaddr*)&this->s_remote,sizeof(this->s_remote))<0){
		cerr<<"Error establishing communications"<<endl;
		close();
	}
}

TCPSocket::TCPSocket(int connected_sock, struct sockaddr_in new_local_addr,	struct sockaddr_in new_remote_addr){

	this->socket_fd = connected_sock;
	this->s_local = new_local_addr;
	this->s_remote = new_remote_addr;
}

TCPSocket* TCPSocket::listenAndAccept(){

	 // Listening for Connection Request
	  listen(socket_fd, 1);

	  unsigned int len = sizeof(this->s_remote);
	  // Accepting a connection request
	  int connect_sock = accept(socket_fd, (struct sockaddr *)&s_remote, &len);
	  if (connect_sock<=0){
		  cerr<<"Error accept connection field"<<endl;
		  return NULL;
	  }

	  return new TCPSocket(connect_sock, this->s_local, this->s_remote);
}

int TCPSocket::recv(char* buffer, int length) {
	return read(this->socket_fd,buffer, length);
}

int TCPSocket::send(const char* msg, int len) {
	return write(socket_fd, msg,len);
}

void TCPSocket::close() {
	::close(socket_fd);
}

string TCPSocket::fromAddr() {
	return inet_ntoa(s_remote.sin_addr);
}


} /* namespace networkingLab */
