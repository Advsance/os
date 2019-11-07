#include "udp_socket.hpp"
int main(){
//  uint16_t port=9000;
  string ip = "192.168.231.133";
  /*
  tmp = argv[2];
  port= tmp;  
  UdpSocket sock;
 // sock.Bind(ip,port);
  string buf;
  string peer_ip;
  uint16_t peer_port;*/
  UdpSocket sock;
  uint16_t port=9900;
  while(1)
  {
 // UdpSocket sock;
  string buf;
  string peer_ip;
  uint16_t peer_port;
    cin>>buf;
    sock.sendTo(buf,ip,port);
    buf.clear();
    sock.RecvFrom(buf,peer_ip,peer_port);
    cout<<"server say fuwuq:"<<buf<<endl;
  }
  sock.Close();
  return 0;
}
