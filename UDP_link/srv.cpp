#include "udp_socket.hpp"
// int main(i, char *argv[]) 
/*
{
  if (argc != 3) {
    cout << "./udp_srv 192.168.122.132 9000\n";
    return -1;
  }
uint16_t port;
string ip = argv[1];
string tmp;
tmp = argv[2];
tmp = port;  */
int main(){
 string ip="192.168.231.133";
uint16_t port = 9900;
UdpSocket sock;
sock.Bind(ip,port);
while(1)
{
  string buf;
  string ip;
uint16_t port;
  sock.RecvFrom(buf,ip,port);
  cout<<"client kehu:"<<buf<<endl;
  buf.clear();
  cin>>buf;
  sock.sendTo(buf,ip,port);
}
 sock.Close();
 return 0;
}
