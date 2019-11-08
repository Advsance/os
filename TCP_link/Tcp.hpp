#include<iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sstream>
#define CHECK_RET(q) if((q)==false){return -1;}

using namespace std;


class TcpSocket{
 private: 
    int _sockfd;
 public:
    bool Socket()
    {
     _sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
     if(_sockfd < 0)
     {
       cerr<<"socket error\n";
       return false ;
     }
       return true ;
    }
    
    bool Bind(const string& ip ,const uint16_t& port)
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
    bool Send(const string& data )
    {
      int ret = send(_sockfd, &data[0], data.size(), 0);
     if(ret < 0)
      {
        cerr<<"Send error"<<endl;
        return false;
      }
      return true;
    }

  bool Recv(string& buf)
  {
    char temp[4096] = {0};
    int  ret = recv(_sockfd , temp, 4095,0);
    if(ret < 0)
    {
      cerr<<"recvfrom erro"<<endl;
      return false;
    }
    if(ret == 0)
    {
      cerr<< "连接以及断开"<<endl;
    }
    buf.assign(temp, ret);
     return true;
  }

  bool Linsten(const int& backlof = 5)
  {
    int re = listen(_sockfd, backlof);
      if(re < 0)
      {
        cerr<<"listen error "<<endl;
        return false;
      }
      return true;
  }

  bool Connect(const string&ip ,const string& port)
  {
    sockaddr_in addr;
    stringstream temp;
    temp<< port;
    uint16_t num;
    temp>>num;
    addr.sin_port = htons(num);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
   int re =  connect(_sockfd, (sockaddr*)&addr, sizeof(addr));
   {
     if(re < 0)
     {
        cerr <<"connect error"<<endl;  
        return false;
     }
      return true;
   }
  }
  
  bool Accept(TcpSocket& clisock, string* ip = NULL, uint16_t* port=NULL )
  {
    sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);//socklen_t 是个
   int re = accept(_sockfd, (sockaddr*)&cliaddr,&len);
    if(re < 0)
    {
      cerr<< "accept error"<<endl;
    }
    clisock._sockfd = re;
    if(ip!=NULL)
    {
      *ip = inet_ntoa(cliaddr.sin_addr);
    }
    if(port!=NULL)
    {
      *port = ntohs(cliaddr.sin_port);
    }
    return true;
  }

  void Close()
  {
    close(_sockfd);
  }

};
