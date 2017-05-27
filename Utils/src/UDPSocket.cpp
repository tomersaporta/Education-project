/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#include "UDPSocket.h"

#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include "UDPSocket.h"
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace networkingLab {


UDPSocket::UDPSocket(int port){
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
		bzero((char*) &s_from, sizeof(s_from));
		bzero((char*) &s_in, sizeof(s_in));
		//sets the sin address
		s_in.sin_family = AF_INET;

		s_in.sin_port = htons(port);
		//bind the socket on the specified address
		if (bind(socket_fd, (struct sockaddr *) &s_in, sizeof(s_in)) < 0) {
			perror("Error naming channel");
		}

}
UDPSocket::~UDPSocket() {
	// TODO Auto-generated destructor stub
}

/**
 * 	- reads an incoming message from the UDP socket. the message is
 * 	copied into the given buffer up to the specified length.
 */
int UDPSocket::recv(char* buffer, int length){
	int rec;
	//bzero((char*)&s_from, sizeof(s_from));
	socklen_t fromSize = sizeof(s_from);
	rec =recvfrom(socket_fd,buffer,length,0,(struct sockaddr *)&s_from, &fromSize);
	//init from ip /port
	this->port= ntohs(s_from.sin_port);
	this->ip=inet_ntoa(s_from.sin_addr);

	printf("UDP server receive ...\n");
	if (rec < 0)
			cout << "Error receive from" << endl;
	cout<<"recvfrom \n"<<endl;
	return rec;
}

/**
 * 	- sends the given message as a UDP message
 * 	to the given address specified by IP and port.
 *
 */
int UDPSocket::sendTo(string msg, string ip, int port){
	struct sockaddr_in s_in;
	int rec;
		bzero((char *) &s_in, sizeof(s_in));
		s_in.sin_family = AF_INET;
		s_in.sin_addr.s_addr = inet_addr(ip.data());
		s_in.sin_port = htons(port);

		rec= sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr*)&s_in,sizeof(s_in));
		if (rec < 0)
				cout << "Error send from" << endl;
		return rec;
	}
/**
 * 	- reply to an incoming message,
 * 	this method will send the given message as a UDP
 * 	message to the peer from which the last message was received.
 *
 */
int UDPSocket::reply(string msg){
	int rec;
	//bzero((char *) &s_from, sizeof(s_from));
	//s_from.sin_family = AF_INET;
	s_from.sin_addr.s_addr = inet_addr(this->ip.data());
    s_from.sin_port = htons(this->port);
	rec =sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr *)&s_from,sizeof(s_from));
	if (rec <0)
		perror("Error reply ");
return rec;
	}
/**
 * - close the UDP socket.
 */
void UDPSocket::close(){
	cout<<"closing socket"<<endl;
		shutdown(socket_fd,SHUT_RDWR);
		::close(socket_fd);
}

/**
 * - return the sender IP of the last received message.
 */
string UDPSocket::fromAddr(){
	return inet_ntoa(s_from.sin_addr);
} /* namespace networkingLab */



}
