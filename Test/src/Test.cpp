/*
 * Test.cpp
 *
 *  Created on: May 2, 2017
 *      Author: user
 */


#include <iostream>
#include "UDPTest.h"
#include "TCPTest.h"
using namespace std;
using namespace networkingLab;

int main() {
	cout << "!!!Hello Testing !!!" << endl; // prints !!!Hello World!!!
// UDP Test
	UDPTest * testUDP = new UDPTest();
	bool res1 = testUDP->test();
	if (res1==true){
		cout<<"TEST UDP PASS"<<endl;
	}else{
		cout <<"TEST UDP FAIL!!!"<<endl;
	}


//TCP Test
	TCPTest *testTCP = new TCPTest();
	bool res2 = testTCP->test();
	if (res2 == true){
		cout<<"TEST TCP PASS"<<endl;
	}else{
		cout <<"TEST TCP FAIL!!!"<<endl;
	}
	return 0;
}
