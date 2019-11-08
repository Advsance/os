#include <iostream>
#include "Tcp.hpp"

int main(int argv ,char* argc[])
{
  if(argv!=3)
  {
    cerr << "输入错误"<<endl;
    return -1;
  }
  stringstream temp;
  string ip(argc[1]);
  uint16_t port;
  temp<<argc[2];
  temp>>port;
  TcpSocket lst_socl;
  CHECK_RET(lst_socl.Socket());
  CHECK_RET(lst_socl.Bind(ip, port));
  CHECK_RET(lst_socl.Linsten());
  while(1)
  {
    TcpSocket cli_sock;
    bool re = lst_socl.Accept(cli_sock);
    if(re == false)
    {
      continue ; 
    }
    int pid = fork();
    if(pid == 0)
    {
      string buff;
      while(1)
      {
        CHECK_RET(cli_sock.Recv(buff));
        cout<<"客户端"<< " "<< buff<<endl;
        buff.clear();
        cout<<"请输入  ";
        cin>>buff;
        CHECK_RET(cli_sock.Send(buff));
      }
    }
  }
}
