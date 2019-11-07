#include "Udp_Socket.hpp"
#include <sstream>

int main(int argc ,char* argv[])
{
  if(argc!=3)
  {
    cerr<< "输入错误"<<endl;
    return -1;
  }
  uint16_t port ;
  string ip = argv[1];
  stringstream temp ;
  temp<<argv[2];
  temp>>port;
  
  UdpSocket sock;
  CHECK_RET(sock.Socket());
  
  while(1)
  {
    string buf;
    cin>>buf;
    sock.Send(buf, ip, port);

    buf.clear();
    sock.Recv(buf, ip , port);
    cout<< "服务器说 "<<buf <<endl;
  }
  sock.Close();
}
