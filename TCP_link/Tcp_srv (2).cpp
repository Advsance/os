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
    string http_req;
    cli_sock.Recv(http_req);
    cout<<http_req<<endl;
    string flist_line="HTTP/1.1 200 ok\r\n";
 //   string body = "<html><body><h1>Hello World</h1></body></html>";
    string body = "<html><body>Hello World</body></html>";
    string len = to_string(body.size());
    string header = "Content-Length: "+ len + "\r\n" ;
    string blank = "\r\n";

    cli_sock.Send(flist_line);
    cli_sock.Send(header);
    cli_sock.Send(blank);
    cli_sock.Send(body);
    cli_sock.Close();
  }
}
