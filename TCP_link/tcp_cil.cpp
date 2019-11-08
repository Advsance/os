#include "Tcp.hpp"
#include <unistd.h>
int main(int argv, char* argc[])
{
  if(argv!=3)
  {
    cerr<<"输入错误"<<endl;
  }
  TcpSocket cil_sock;
 CHECK_RET(cil_sock.Socket());
 CHECK_RET(cil_sock.Connect(argc[1], argc[2]));
 while(1)
 {
   string temp;
   cout<<"请输入你要说的话: ";
   cin>>temp;
   CHECK_RET(cil_sock.Send(temp));
   temp.clear();
   CHECK_RET(cil_sock.Recv(temp));
   cout<<"服务器说: "<<temp<<endl;
 }

  return 0;
}
