#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <cassert>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
using namespace std;
class  UdpSocket{
  public:
    UdpSocket()
      :_fd(-1)
    {
      _fd = socket(AF_INET,SOCK_DGRAM,0);
      if(_fd<0)
     {
       cout<<"Create a Failure"<<endl;
     }
    }      
    bool Close(){
      close(_fd);
      return true ;
    }
    bool Bind(const string& ip,uint16_t port){
     sockaddr_in addr;
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=inet_addr(ip.c_str());
     addr.sin_port=port;
    int ret = bind(_fd,(sockaddr*)&addr,sizeof(addr));
    cout<<"bind succeed"<<endl;
    if(ret<0)
    {
      perror("bind");
      return false;
    }
    return true;
    }
    bool RecvFrom(string& buf,string& ip , uint16_t& port){
    char temp[1024*10]={0};
    sockaddr_in peer;
    socklen_t len=sizeof(peer);
    int ret = recvfrom(_fd,temp,sizeof(temp)-1,0,(sockaddr*)& peer ,&len);
    if(ret<0)
    {
      perror("recvfrom");
      return false;
    }
      ip =inet_ntoa(peer.sin_addr);   
      port=ntohs(peer.sin_port);
    buf.assign(temp,ret);
    return true;
    }
    bool sendTo(const string& buf ,const string& ip,uint16_t port)
    {
       sockaddr_in addr;
       addr.sin_family = AF_INET;
       addr.sin_port = htons(port);
       addr.sin_addr.s_addr = inet_addr(ip.c_str());
       ssize_t write_size=sendto(_fd,buf.data(),buf.size(),
                 0,(sockaddr*)&addr,sizeof(addr));
      if(write_size<0)
      {
        perror("sendto");
        return false;
      }
       return true;
    }
  private:
    int _fd;
 };
