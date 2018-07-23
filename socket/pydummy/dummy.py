#!/usr/bin/env python
# -*- coding:utf8 -*-
 
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import socket
#HOST = "127.0.0.1"
HOST = "192.168.7.201"
PORT = 4030


class UdpServer(object):
    def udpServer(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind((HOST,PORT))
        
        while True:
            revcData, (remoteHost, remotePort) = sock.recvfrom(1024)
            print("[%s:%s] connect" % (remoteHost, remotePort))

            print "revcData: ", revcData
            sendData = sock.sendto(revcData, (remoteHost, remotePort))
            
            
        sock.close()
           
if __name__ == "__main__":
    udpServer = UdpServer()
    udpServer.udpServer()
