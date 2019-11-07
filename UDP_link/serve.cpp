#include "Udp_Socket.hpp"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc !=3 )
  {
    std:: cerr<<"输入有误"<<endl;
    return -1;
  }
  uint16_t port;
  string ip = argv[1];
  stringstream tmp;
  tmp<< argv[2];
  tmp>>port;
  UdpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip, port));
  
  while(1)
  {
    string buf;
    string ip;
    uint16_t port;
    sock.Recv(buf, ip, port);
    cout<<"接收到:"<< buf<<endl;
    buf.clear();
    cin>>buf;
    sock.Send(buf, ip ,port);
  }
   sock.Close(); 
}
  
