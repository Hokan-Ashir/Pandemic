/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Socket' to communicate with external computers through the internet.

/******************************************************************************/
#define NULL_SOCKET Ptr(~0)
/******************************************************************************/
struct SockAddr // Socket Address
{
   // get/set single value
   Int  port()C;   SockAddr& port(Int  port);
   UInt ip  ()C;   SockAddr& ip  (UInt ip  );   SockAddr& ip(C Str8 &ip);   Str8 ipText()C;

   Bool valid()C {return ip()!=0;} // if socket address is valid

   // set
   SockAddr& clear       (                      ); // clear address to zero
   Bool      setFrom     (C Socket &socket      ); // set address from socket
   SockAddr& setServer   (              Int port); // set address to be used for creating a server
   SockAddr& setLocalFast(              Int port); // set address to local host (  fast                 ip will be used "127.0.0.1"), this allows connections only within the same computer
   SockAddr& setLocal    (              Int port); // set address to local host ( local                 ip will be used            ), this allows connections only within the same computer and local network (connecting beyond local network depends if the local host is behind a router)
   Bool      setGlobal   (              Int port); // set address to local host (global/public/external ip will be used            ), this allows connections      within the same computer,    local network and beyond (resolving global ip address requires connecting to external websites !!)
   Bool      setHost     (C Str  &host, Int port); // set address to host from its name, false on fail
   SockAddr& setIP       (  UInt  ip  , Int port); // set address to direct ip address
   Bool      setIP       (C Str8 &ip  , Int port); // set address to direct ip address , false on fail

   Bool setFtp (C Str &host) {return setHost(host, 21);}
   Bool setHttp(C Str &host) {return setHost(host, 80);}

   // conversions
   Str    asText(               )C; // get address as   text in IP:PORT format (x.y.z.w:p)
   Bool fromText(C Str8 &ip_port) ; // set address from text in IP:PORT format (x.y.z.w:p), false on fail

   // io
   void save(File &f)C; // save address to   file,
   Bool load(File &f) ; // load address from file, false on fail

   SockAddr() {clear();}

private:
   UInt _address[4];
};
// compare
       Int  Compare   (C SockAddr &a, C SockAddr &b);                           // compare
inline Bool operator==(C SockAddr &a, C SockAddr &b) {return Compare(a, b)==0;} // if     equal
inline Bool operator!=(C SockAddr &a, C SockAddr &b) {return Compare(a, b)!=0;} // if not equal
/******************************************************************************/
struct Socket
{
   enum RESULT
   {
      FAILED     , // couldn't connect
      CONNECTED  , // connected successfully
      IN_PROGRESS, // still connecting, you can verify the connection state at a later time using 'connectFailed' method
   };

   // manage
   void del      (); // delete
   Bool createTcp(); // create Tcp socket, false on fail, TCP protocol description: data is     guaranteed to reach the target, data is     always received in the same order as it was sent, sending multiple small packets may   result  in groupping them together and sending as one big packet
   Bool createUdp(); // create Udp socket, false on fail, UDP protocol description: data is not guaranteed to reach the target, data is not always received in the same order as it was sent, sending multiple small packets never results in groupping them together and sending as one big packet

   // get
   Bool     is  ()C {return _s!=NULL_SOCKET;} // if  socket is valid
   Int      port()C;                          // get socket port
   UInt     ip  ()C;                          // get socket ip address
   SockAddr addr()C;                          // get socket    address

   // set
   Bool block     (Bool on); // set blocking mode     , false on fail
   Bool tcpNoDelay(Bool on); // set TCP_NODELAY option, false on fail

   // operations
   Bool   bind   (C SockAddr &addr                ); // bind    socket to specific address, false on fail
   RESULT connect(C SockAddr &addr, Int timeout=-1); // connect socket to specific address, 'timeout'=how long (in milliseconds) to wait for a connection (<0 use default value specified by the OS, for >=0 values the socket will automatically be converted into non-blocking mode)
   Bool   connectFailed(                          ); // you can use this method after getting IN_PROGRESS result from 'connect' method to test if the connection attempt has failed

   Bool listen(                                  ); // start  listening for incoming connections  , false on fail
   Bool accept(Socket &connection, SockAddr &addr); // accept incomming connection and its address, false on fail, upon success 'connection' and 'addr' will be set according to the incomming connection properties

   // io
   Int send   (                  CPtr data, Int size); // send    'data'                           , returns the size of sent     data (-1 on fail            )
   Int receive(                   Ptr data, Int size); // receive 'data'                           , returns the size of received data (-1 if no data awaiting)
   Int send   (C SockAddr &addr, CPtr data, Int size); // send    'data' to   'addr' socket address, returns the size of sent     data (-1 on fail            ), this method is available only for UDP sockets
   Int receive(  SockAddr &addr,  Ptr data, Int size); // receive 'data' from 'addr' socket address, returns the size of received data (-1 if no data awaiting), this method is available only for UDP sockets, if any data was received then 'addr' will be set to the address of the sender

   Bool wait (Int time); // wait 'time' milliseconds for data arrival                  , false on timeout
   Bool flush(Int time); // wait 'time' milliseconds until the data has been sent fully, false on timeout
   Bool any  (Int time); // wait 'time' milliseconds for any 'wait' or 'flush' event   , false on timeout

   Int available()C; // get number of bytes available for reading, -1 on fail

  ~Socket() {del();}
   Socket() {_s=NULL_SOCKET;}

private:
   Ptr _s;
   NO_COPY_CONSTRUCTOR(Socket);
};
/******************************************************************************/
ULong GetMac(); // get computer's MAC address

void       GetGlobalIP(Bool refresh=false); // initiate        obtaining global ip address in the background, 'refresh'=if ignore previously obtained ip address and try getting a new one in case it was changed
Bool       HasGlobalIP(                  ); // if successfully obtained  global ip address
Bool ObtainingGlobalIP(                  ); // if currently    obtaining global ip address

void GetLocalAddresses(Memp<SockAddr> addresses,              Int port=0); // get a list of all known addresses for local     host
void GetHostAddresses (Memp<SockAddr> addresses, C Str &host, Int port=0); // get a list of all known addresses for specified host

Bool SendMailSupported(); // check if 'SendMail' function is supported on this machine, this function should not be called before 'InitPre'
Bool SendMail(C Str &from_name, C Str &from_email, C Str &to_name, C Str &to_email, C Str &subject, C Str &message); // send e-mail using local host as SMTP server, 'from_name'=name of the sender (example "John Smith"), 'from_email'=sender e-mail address (example "user@domain.com"), 'to_name'=name of the recipent (example "Jane Smith"), 'to'=recipent e-mail address (example "user@domain.com"), 'subject'=subject, 'message'=e-mail message
/******************************************************************************/
