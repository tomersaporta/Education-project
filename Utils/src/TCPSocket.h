/*
 * TCPSocket.h
 *
 *  Created on: Apr 24, 2017
 *      Author: user
 */

#ifndef SRC_TCPSOCKET_H_
#define SRC_TCPSOCKET_H_

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>



using namespace std;

namespace networkingLab {

class TCPSocket
{
public:

	int socket_fd;
	struct sockaddr_in s_local;
	struct sockaddr_in s_remote;

	TCPSocket();
	virtual ~TCPSocket();
	// - construct-or to create a TCP server socket.
	TCPSocket(size_t port);
	 //- constructor to creates TCP client socket and connect it to the remote peer in the given ip and port.
	TCPSocket(string peerIp, size_t port);
	//- constructor to creates TCP new client socket of new connection
	TCPSocket(int connected_sock, struct sockaddr_in new_local_addr,	struct sockaddr_in new_remote_addr);
	//- perform listen and accept on server socket,this function returns a new TCPSocket object to communicate over the incoming session.
	TCPSocket* listenAndAccept();
	// - read from socket into the given buffer up to the buffer given length, return the number of bytes read.
	int recv(char* buffer, int length);
	// - send the given buffer to the socket.
	int send(const char* msg, int len);
	// - close the socket and free all resources.
	void close();
	// - return the address of the connected peer.
	string fromAddr();

};

} /* namespace networkingLab */

#endif /* SRC_TCPSOCKET_H_ */
