#include<iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define CHECK_RET(q) if((q)==false){return -1;}

using namespace std;


class UdpSocket{
 private: 
    int _sockfd;
 public:
    bool Socket()
    {
     _sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
     if(_sockfd < 0)
     {
       cerr<<"socket error\n";
       return false ;
     }
       return true ;
    }
    
    bool Bind(const string& ip ,const uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family=AF_INET; // 用的什么类型的IP
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int len = sizeof(addr);
      int ret = bind(_sockfd, (sockaddr*)&addr, len);
       if(ret < 0)
       {
          cerr<<"Bind error"<<endl; 
          return false ;
       }
       return true;
    }
    // 发送数据
    bool Send(const string& data ,const string& ip,const u_int16_t& port)
    {
      sockaddr_in addr;
      addr.sin_port = htons(port);
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      int ret = sendto(_sockfd, &data[0], data.size(), 0,(sockaddr*)&addr,sizeof(addr));
      if(ret < 0)
      {
        cerr<<"Send error"<<endl;
        return false;
      }
      return true;
    }

  bool Recv(string& buf,string& ip, uint16_t& port)
  {
    sockaddr_in temp_addr;
    char temp[4096] = {0};
    socklen_t len = sizeof(temp_addr); //  注意 socklen_t 这个数据类型不能写错
    int  ret = recvfrom(_sockfd, temp, 4095, 0, (sockaddr*)&temp_addr, &len);
    if(ret < 0)
    {
      cerr<<"recvfrom erro"<<endl;
      return false;
    }
     ip = inet_ntoa(temp_addr.sin_addr);
     port = ntohs(temp_addr.sin_port);
     buf.assign(temp,ret);
     return true;
  }

  void Close()
  {
    close(_sockfd);
  }

};
