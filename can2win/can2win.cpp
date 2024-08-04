/*
The MIT License (MIT)

Copyright (c) 2018, Thomas Dahlmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <linux/can.h>
#include <linux/can/raw.h>

#include <endian.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include <cerrno>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>


#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#include <pthread.h>

#include <iostream>
#include <fstream>
#include <string>

#include <map>

#define PROGNAME  "sockcan"
#define VERSION  "1.0.0"

// tom tcp spock
// make server

using namespace std;
 
// CAN FD TCP socket buffer offsets defs
#define CANPP_SOCKET_BUF_LEN_OFS 0
#define CANPP_SOCKET_BUF_LEN_SIZE 2
#define CANPP_SOCKET_BUF_COMMAND_OFS 2
// COMMANDS
#define CANPP_SOCKET_BUF_COMMAND_CONNECT 0x01
#define CANPP_SOCKET_BUF_COMMAND_DISCONNECT 0x02
#define CANPP_SOCKET_BUF_COMMAND_ALIVE 0x04
#define CANPP_SOCKET_BUF_COMMAND_CAN_MASK 0x80
// CAN COMMAND
#define CANPP_SOCKET_BUF_CANID_OFS 3
#define CANPP_SOCKET_BUF_CHANNEL_OFS 7
#define CANPP_SOCKET_BUF_DIR_DLC_OFS 8
#define CANPP_SOCKET_BUF_DIR_MASK 0x80
#define CANPP_SOCKET_BUF_DLC_MASK 0x07f
#define CANPP_SOCKET_BUF_DATA_OFS 9

// TCP socket frame defines
/*#define CANPP_SOCKET_BUF_DATA_OFS 4
#define CANPP_SOCKET_BUF_CHANNEL_OFS 12
#define CANPP_SOCKET_BUF_DIR_OFS 13
#define CANPP_SOCKET_BUF_DLC_OFS 14
#define CANPP_SOCKET_BUF_COMMAND_OFS 15
#define CANPP_SOCKET_BUF_COMMAND_CONNECT 0x01
#define CANPP_SOCKET_BUF_COMMAND_DISCONNECT 0x02
#define CANPP_SOCKET_BUF_COMMAND_ALIVE 0x04*/

// TCP
#define CANPP_MAX_NUM_TCP_CLIENTS 100
#define TCP_SEND_BUFFER_LEN 50000
#define TCP_RECV_BUFFER_LEN 50000
 
// LEDs
#define LED0_PATH "/sys/class/leds/beaglebone:green:usr0"
#define LED1_PATH "/sys/class/leds/beaglebone:green:usr1"
#define LED2_PATH "/sys/class/leds/beaglebone:green:usr2"
#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"
std::fstream fs;

// Options
char interface[20][50];
int numInterfaces = 0;

// sockets
int listenfd = 0, connfd = 0;
struct sockaddr_in serv_addr; 

//unsigned char sendBuff[10000];
pthread_t threadId;

// sockcan hdl struct
typedef struct {
    int sockcan_sock;
    int sockcan_ix;
    int tcp_sock;
    
} socks_data_t;

// client map
typedef struct {
    char ip_str[20];
    pthread_mutex_t mutexTcpSend;    
} my_sockaddr_data;

std::map<unsigned long, my_sockaddr_data*> g_clientSockMap;
//std::map<int, char*> g_clientSockMap;

// udp
unsigned long last_ipaddr = 0;
//struct sockaddr_in claddr;  // address of the client
// socklen_t clientlen;
my_sockaddr_data g_txCladdrData;  // address of the client

int firstPacketFromClient = 0;

// tcp
//int connected = 0;
pthread_mutex_t mutexClientSockMap = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutexTcpSend = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutexTcpRecv = PTHREAD_MUTEX_INITIALIZER;
int numClients = 0;


std::sig_atomic_t signalValue;

// tom
void removeTrigger(){
   // remove the trigger from the LED
   //std::fstream fs;
   fs.open( LED0_PATH "/trigger", std::fstream::out);
   fs << "none";
   fs.close();

   fs.open( LED1_PATH "/trigger", std::fstream::out);
   fs << "none";
   fs.close();
   
   fs.open( LED2_PATH "/trigger", std::fstream::out);
   fs << "none";
   fs.close();

   fs.open( LED3_PATH "/trigger", std::fstream::out);
   fs << "none";
   fs.close();
   
}

void onSignal(int value) {
    signalValue = static_cast<decltype(signalValue)>(value);
}


int sockList[CANPP_MAX_NUM_TCP_CLIENTS];

/*-----------------------------------------------------------------------------------------------
    Function:
  -----------------------------------------------------------------------------------------------*/
void dump_buffer(unsigned char *buf, int count)
{
     int i;
     printf("dump %d bytes:\n", count);
     for (i = 0; i < count; i++)
     {          
          printf("%02x ", *(buf + i));
     }
     printf("\n");
}

//} // namespace

int canpp_TcpRecvAll(int sock, char *buf, int *len)
{
    int total = 0;        
    int bytesleft = *len;
    int n;

    //pthread_mutex_lock(&mutexTcpRecv);
    while(total < *len) {
          n = recv(sock, buf+total, bytesleft, 0);
          if (n == -1)
          {
               break;
          }
          if (n == 0)
          {
               total = 0;
               break;
          }          
          total += n;
          //VERBOSE_PRINT("total = %d\n", total);
          bytesleft -= n;
    }
    //pthread_mutex_unlock(&mutexTcpRecv);

    *len = total;

    if (n <= 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }

} 

// TCP send all
int canpp_TcpSendAll(int sock, char *buf, int *len)
{
    int total = 0;        
    int bytesleft = *len;
    int n;

    //pthread_mutex_lock(&mutexTcpSend);
    while(total < *len) {
          n = send(sock, buf+total, bytesleft, 0);
          if (n == -1)
          {
               break;
          }
          total += n;
          bytesleft -= n;
    }
    //pthread_mutex_unlock(&mutexTcpSend);

    *len = total;

    if (n == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }

} 

void print_client_map()
{
    map<unsigned long, my_sockaddr_data*>::iterator it;
    //map<int, char*>::iterator it;    
    printf("clients socks:\n");
    pthread_mutex_lock(&mutexClientSockMap);
    for (it = g_clientSockMap.begin(); it != g_clientSockMap.end(); it++)
    {
        printf("client %s\n", it->second->ip_str);
    }
    pthread_mutex_unlock(&mutexClientSockMap);      
}
////////////////////////////////////////////////////////////////////////////////////
// sockcan handler
////////////////////////////////////////////////////////////////////////////////////
void *sockcan_handler(void *socketDesc)
{
    socks_data_t socks_data;
    
    int sockfd,sock;
    int canSockIx;
    int connected = 1;
        
    char sendBuff[TCP_SEND_BUFFER_LEN];
    int len, dataLen, payloadLen;
    
    
    // init threads
    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    printf("started sockcan handler\n");
    
    memcpy(&socks_data, (socks_data_t*) socketDesc, sizeof(socks_data_t));
    sockfd = socks_data.sockcan_sock;
    canSockIx = socks_data.sockcan_ix;
    sock = socks_data.tcp_sock;
    
    // send mutex
    pthread_mutex_t* sendMutex;
    sendMutex = &(g_clientSockMap[sock]->mutexTcpSend);
            
    // Main loop
    // delay can sending
    //sleep(1);
    while (connected)
    {
        struct canfd_frame frame;

        // Read in a CAN frame
        //printf ("read on can sock=%d\n", sockfd);
        auto numBytes = ::read(sockfd, &frame, CANFD_MTU);
        //printf ("got on can sock=%d, %d bytes\n", sockfd, numBytes);
        switch (numBytes) {
        case CANFD_MTU:
        case CAN_MTU:
            // process frame
  
            // can id
            sendBuff[CANPP_SOCKET_BUF_CANID_OFS + 0] = (frame.can_id & 0xff000000) >> 24;
            sendBuff[CANPP_SOCKET_BUF_CANID_OFS + 1] = (frame.can_id & 0x00ff0000) >> 16;
            sendBuff[CANPP_SOCKET_BUF_CANID_OFS + 2] = (frame.can_id & 0x0000ff00) >> 8;
            sendBuff[CANPP_SOCKET_BUF_CANID_OFS + 3] = (frame.can_id & 0x000000ff);                
            // channel
            sendBuff[CANPP_SOCKET_BUF_CHANNEL_OFS] = canSockIx;
            // RX /TX
            sendBuff[CANPP_SOCKET_BUF_DIR_DLC_OFS] = 0;
            // DLC
            dataLen = frame.len & CANPP_SOCKET_BUF_DLC_MASK;
            sendBuff[CANPP_SOCKET_BUF_DIR_DLC_OFS] |= dataLen;
            // data
            memcpy(sendBuff + CANPP_SOCKET_BUF_DATA_OFS, frame.data, dataLen);
            // TCP len
            len = CANPP_SOCKET_BUF_DATA_OFS + dataLen; 
            payloadLen = len - CANPP_SOCKET_BUF_LEN_SIZE; 
            sendBuff[CANPP_SOCKET_BUF_LEN_OFS] = (payloadLen & 0xff00) >> 8;
            sendBuff[CANPP_SOCKET_BUF_LEN_OFS + 1] = payloadLen & 0xff;
            
            //printf ("got canSockIx=%d sock=%d canid %x mapsize=%d\n", canSockIx, sockfd, frame.can_id, g_clientSockMap.size());
            //dump_buffer((unsigned char*) sendBuff, len);

            
                        
            // send to Tcp client
            
            //send(sock, sendBuff, 16, 0);
            pthread_mutex_lock(sendMutex);
            canpp_TcpSendAll(sock, sendBuff, &len);
            pthread_mutex_unlock(sendMutex);
       
            break;
        /*case CANFD_MTU:
            // TODO: CAN FD
            std::perror("CANFD read");
            connected = 0;
            break;*/
        case -1:
            printf("CAN sockfd=%d", sockfd);
            std::perror("CAN read");
            connected = 0;
            //std::this_thread::sleep_for(100ms);
        default:
            continue;
        }
    }    
    
    
   
    
    
    printf("Exit sockcan_handler() for sock %d\n", sock);

} 

////////////////////////////////////////////////////////////////////////////////////
// alive handler
////////////////////////////////////////////////////////////////////////////////////
void *alive_handler(void *socketDesc)
{
    int sock = *(int*)socketDesc;
    int readSize;
    char aliveTxBuf[16];
    int n;
    unsigned short len = 0;
    
   
    // init threads
    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    printf("started alive handler\n");
    
    // send mutex
    pthread_mutex_t* sendMutex;
    sendMutex = &(g_clientSockMap[sock]->mutexTcpSend);
    
    int connected = 1;
    while (connected)
    {              
            // send alive
            aliveTxBuf[CANPP_SOCKET_BUF_COMMAND_OFS] = CANPP_SOCKET_BUF_COMMAND_ALIVE;
            //aliveTxBuf[CANPP_SOCKET_BUF_DLC_OFS] = 0;
              
            //n = send(sock, aliveTxBuf, 16, 0);
            int len = 1;
            aliveTxBuf[CANPP_SOCKET_BUF_LEN_OFS + 1] = len & 0xff;
            aliveTxBuf[CANPP_SOCKET_BUF_LEN_OFS] = (len & 0xff00) >> 8;
            // add len bytes
            len += CANPP_SOCKET_BUF_LEN_SIZE;

            //dump_buffer((unsigned char*) aliveTxBuf, 16);
           
            pthread_mutex_lock(sendMutex);
            n = canpp_TcpSendAll(sock, aliveTxBuf, &len);
            pthread_mutex_unlock(sendMutex);

            if (n < 0) {
                perror("alive: cannot send()");                
                connected = 0;
                //return 0; 
            }       
            sleep(1);
    }
    
    printf("Exit alive_handler() for sock %d\n", sock);

    return 0;
} 

////////////////////////////////////////////////////////////////////////////////////
// receive TCP packet from PC and send on CAN bus
////////////////////////////////////////////////////////////////////////////////////
void *write_handler(void *socketDesc)
{
    int sock = *(int*)socketDesc;
    int readSize;
    char rxbuffer[TCP_RECV_BUFFER_LEN];
    int n;    
    int connected = 1;
    
    struct canfd_frame frame;

    // init threads
    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    // sockcan
    int* sockfd = NULL;
    int channel;
    int i;
    int rc;
    // CAN connection variables
    struct sockaddr_can addr;
    struct ifreq ifr;
    int recv_own_msgs = 1; /* 0 = disabled (default), 1 = enabled */   

    printf("started write handler\n");
    

    sockfd = (int*) malloc(numInterfaces * sizeof(int));
    if (sockfd == NULL)
    {
        std::perror("malloc");
        return 0;
    }
    
    // open all CAN interfaces
    socks_data_t socks_data[512];
    for (int i = 0; i < numInterfaces; i++)
    {

        // sockcan open
        // Open the CAN network interface
        sockfd[i] = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if (-1 == sockfd[i]) {
            std::perror("socket");
            goto errSocket;
        }
        // Enable CAN FD frames
        {
            int enable = 1;

            rc = ::setsockopt(
                sockfd[i],
                SOL_CAN_RAW,
                CAN_RAW_FD_FRAMES,
                &enable,
                sizeof(enable)
            );
            if (-1 == rc) {
                std::perror("setsockopt CAN FD");
                goto errSetup;
            }
        }
        printf("interface name [%d]: %s, socket id = %d\n", i, &(interface[i][0]), sockfd[i]);


        // Set a receive filter so we only receive select CAN IDs
        {
            struct can_filter filter[2];
            filter[0].can_id   = 0x7ed;
            filter[0].can_mask = CAN_SFF_MASK;
            filter[1].can_id   = 0x7e5;
            filter[1].can_mask = CAN_SFF_MASK;
            /*filter[2].can_id   = 0x191;
            filter[2].can_mask = CAN_SFF_MASK;*/

            /*rc = ::setsockopt(
                sockfd[i],
                SOL_CAN_RAW,
                CAN_RAW_FILTER,
                &filter,
                sizeof(filter)
            );
            if (-1 == rc) {
                std::perror("setsockopt filter");
                goto errSetup;
            }*/
        }

        // Enable reception of CAN FD frames
        {
            int enable = 1;

            rc = ::setsockopt(
                sockfd[i],
                SOL_CAN_RAW,
                CAN_RAW_FD_FRAMES,
                &enable,
                sizeof(enable)
            );
            if (-1 == rc) {
                std::perror("setsockopt CAN FD");
                goto errSetup;
            }
        }
        
        // receive own messages
        /*rc = setsockopt(sockfd[i], SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS,
                   &recv_own_msgs, sizeof(recv_own_msgs));    
        if (-1 == rc) {
                std::perror("setsockopt CAN_RAW_RECV_OWN_MSGS");
                goto errSetup;
        }*/               

        // Get the index of the network interface
        std::strncpy(ifr.ifr_name, &(interface[i][0]), IFNAMSIZ);
        if (::ioctl(sockfd[i], SIOCGIFINDEX, &ifr) == -1) {
            std::perror("ioctl sock can");
            goto errSetup;
        }

        // Bind the socket to the network interface
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;
        rc = ::bind(
            sockfd[i],
            reinterpret_cast<struct sockaddr*>(&addr),
            sizeof(addr)
        );
        if (-1 == rc) {
            std::perror("bind sock can");
            goto errSetup;
        }        
        
        // sockcan handler
        printf("new sockcan handler\n");
        //socks_data_t socks_data;
        
        socks_data[i].sockcan_sock = sockfd[i];
        socks_data[i].sockcan_ix = i;
        socks_data[i].tcp_sock = sock;
        printf("interace %s => channel %d\n", &(interface[i][0]), i + 1);
        
        if( pthread_create( &threadId , NULL ,  sockcan_handler , (void*) &(socks_data[i])) < 0)
        {
            perror("could not create sockcan  thread");
                       
            return 0;
        }  
    }
    
    // send mutex
    pthread_mutex_t* sendMutex;
    sendMutex = &(g_clientSockMap[sock]->mutexTcpSend);
    
    int len;
    /////////////////////////////////////////////////////////////////////////////////////////
    while (connected)
    {              

            //printf("write thread: wait for data\n");
            
            // receive TCP packet from PC 
            //printf("wait for recv()\n");
            //n = recv(sock, rxbuffer, 16, 0);

            // get len 
            len = CANPP_SOCKET_BUF_LEN_SIZE;
            n = canpp_TcpRecvAll(sock, rxbuffer, &len);
            if (n < 0) {
                perror("cannot recv()");
                firstPacketFromClient = 0;
                connected = 0;
                break;                
            } 
            len = rxbuffer[1] & 0xff;
            len = len | ((rxbuffer[0] & 0xff) << 8);

            // recv data
            //len = 16;
            n = canpp_TcpRecvAll(sock, rxbuffer + CANPP_SOCKET_BUF_LEN_SIZE, &len);
            //printf("after recv() bytes = %d\n", n);
            if (n < 0) {
                perror("cannot recv()");
                firstPacketFromClient = 0;
                connected = 0;                
            } 
            else if (rxbuffer[CANPP_SOCKET_BUF_COMMAND_OFS] == CANPP_SOCKET_BUF_COMMAND_ALIVE)
            {
                // ignore
                //printf("alive rx, sock = %d\n", sock);
            }
            else
            {                
               
                //printf("got %d bytes\n", n);                
                               
                
                //last_ipaddr = rxCladdr.sin_addr.s_addr;
            
                //print_client_map();
                                    
                /*n = read(connfd, rxbuffer, 12);
                if (n == 0)
                {
                    printf("write thread: disconnected\n");
                    return 0;                
                }*/
                //printf("write thread: received %d bytes\n", n);
                // can id            
                frame.can_id = rxbuffer[CANPP_SOCKET_BUF_CANID_OFS + 0] << 24;
                frame.can_id |= rxbuffer[CANPP_SOCKET_BUF_CANID_OFS + 1] << 16;
                frame.can_id |= rxbuffer[CANPP_SOCKET_BUF_CANID_OFS + 2] << 8;
                frame.can_id |= rxbuffer[CANPP_SOCKET_BUF_CANID_OFS + 3];           
                //printf("send canid = %x, sockfd=%d, sock=%d\n", frame.can_id, sockfd, sock);
                /*printf("write thread: received for can id %x\n", frame.can_id);
                printf("write thread: buf0 %x\n", rxbuffer[4]);
                printf("write thread: buf1 %x\n", rxbuffer[5]);
                printf("write thread: buf2 %x\n", rxbuffer[6]);
                printf("write thread: buf3 %x\n", rxbuffer[7]);
                printf("write thread: buf4 %x\n", rxbuffer[8]);
                printf("write thread: buf5 %x\n", rxbuffer[9]);
                printf("write thread: buf6 %x\n", rxbuffer[10]);
                printf("write thread: buf7 %x\n", rxbuffer[11]);
                printf("write thread: cmd(15) %x\n", rxbuffer[15]);*/

                channel = rxbuffer[CANPP_SOCKET_BUF_CHANNEL_OFS] & 0xff;
                if (channel > numInterfaces - 1)
                {
                    channel = 0;
                    rxbuffer[CANPP_SOCKET_BUF_CHANNEL_OFS] = 0;
                }
                
                // ignore init packet for firewall
                //if (frame.can_id != 0xffffffff)
                {
                    // data
                    // DLC and DIR
                    //frame.len = 0;
                    frame.len = rxbuffer[CANPP_SOCKET_BUF_DIR_DLC_OFS] & CANPP_SOCKET_BUF_DLC_MASK;
                   
                    //if (rxbuffer[CANPP_SOCKET_BUF_DLC_OFS] <= 8 && rxbuffer[CANPP_SOCKET_BUF_DLC_OFS] != 0)
                    //    frame.len = rxbuffer[CANPP_SOCKET_BUF_DLC_OFS];
                    
                    
                    //memcpy(frame.data, rxbuffer + CANPP_SOCKET_BUF_DATA_OFS, 8);
                    memcpy(frame.data, rxbuffer + CANPP_SOCKET_BUF_DATA_OFS, frame.len);
                    
                    // send to CAN
                    //auto numBytes = ::send(sockfd, &frame, CANFD_MTU);
                    int nbytes;
                    if (frame.len)
                    {
                        nbytes = write(sockfd[channel], &frame, sizeof(struct canfd_frame));
                    }
                    
                    // send packet back to own client as TX as own send sockcan messages are not in sockcan rx      
                    // channel
                    //rxbuffer[CANPP_SOCKET_BUF_CHANNEL_OFS] = 0;
                    // RX /TX
                    rxbuffer[CANPP_SOCKET_BUF_DIR_DLC_OFS] |= 0x80;
                    
                    //rxbuffer[CANPP_SOCKET_BUF_CHANNEL_OFS] = 0;
                    // RX /TX
                    //rxbuffer[CANPP_SOCKET_BUF_DIR_OFS] = 1;
                    //sendto(listenfd, rxbuffer, 16, 0, (struct sockaddr*) &rxCladdr, rxClientlen);
                    //nbytes = send(sock, rxbuffer, 16, 0);
                    //len = 16;
                    len = len + CANPP_SOCKET_BUF_LEN_SIZE;
                    pthread_mutex_lock(sendMutex);
                    canpp_TcpSendAll(sock, rxbuffer, &len);
                    pthread_mutex_unlock(sendMutex);
                    if (len < 0)                         
                    {
                        perror("write handler: tcp send");
                        connected = 0;
                    }
                    
                    //sendto(sockfd, frame, sizeof(struct can_frame), 0, (struct sockaddr*) &claddr, clientlen)
                }
            
            }
   
 
    }
 
   // Error handling (reverse order cleanup)
errSetup:
    for (int i = 0; i < numInterfaces; i++)
        ::close(sockfd[i]);
errSocket:  
     
    printf("Exit write_handler() for sock %d and sockcan %d\n", sock, sockfd);
    // erase sock from map
    pthread_mutex_lock(&mutexClientSockMap);    
    if (g_clientSockMap[sock])
        delete g_clientSockMap[sock];
    g_clientSockMap.erase(sock);            
    pthread_mutex_unlock(&mutexClientSockMap);       

    close(sock);
    free(sockfd);

    return 0;
} 
////////////////////////////////////////////////////////////////////////////////////
// accept handler
////////////////////////////////////////////////////////////////////////////////////
void *accept_handler(void *listenDesc)
{
    int localListenfd = *(int*)listenDesc;
    struct sockaddr_in servAddr, cliAddr;
    socklen_t clilen;
    int n;
    
    clilen = sizeof(cliAddr);
    
    // init threads
    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    // wait for clients
    pthread_mutex_init(&mutexClientSockMap, NULL);    
    
    listen(localListenfd, 10);
    
    connfd = accept(localListenfd, (struct sockaddr *)&cliAddr, (socklen_t*)&clilen);
    //connfd = accept(localListenfd, (struct sockaddr *)NULL, NULL);
    
    printf("\n wait for clients\n");
    char clientIp[1024];
    while (connfd > 0)
    {        
        //char *clientIp = new char[20];
        my_sockaddr_data* sock_data = new my_sockaddr_data;
        
        // recv timeout
        struct timeval tv;
        tv.tv_sec = 7; //  sec
        tv.tv_usec = 0;
        n = setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
        if (n < 0)
            perror("Error set recv timeout");
        
        
        //connected = 1;
        sprintf(clientIp, "%d.%d.%d.%d",
                    (int) (cliAddr.sin_addr.s_addr&0xFF),
                    (int) ((cliAddr.sin_addr.s_addr&0xFF00)>>8),
                    (int) ((cliAddr.sin_addr.s_addr&0xFF0000)>>16),
                    (int) ((cliAddr.sin_addr.s_addr&0xFF000000)>>24));
                    
        printf("\nClient IP address %s\n", clientIp);
                    
                
                
        pthread_mutex_lock(&mutexClientSockMap);   
        strcpy(sock_data->ip_str, clientIp);     
        sock_data->mutexTcpSend = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&(sock_data->mutexTcpSend), NULL);    
        g_clientSockMap[connfd] = sock_data;
        //g_clientSockMap[connfd] = clientIp;
        pthread_mutex_unlock(&mutexClientSockMap);

        print_client_map();        
              
        
        // write handler
        printf("new write handler\n");
        if( pthread_create( &threadId , NULL ,  write_handler , (void*) &connfd) < 0)
        {
            perror("could not create write  thread");
            
            pthread_mutex_lock(&mutexClientSockMap);    
            if (g_clientSockMap[connfd])
                delete g_clientSockMap[connfd];
            g_clientSockMap.erase(connfd);            
            pthread_mutex_unlock(&mutexClientSockMap);            
            
            return 0;
        }
        
        // alive handler
        printf("new alive handler\n");
        if( pthread_create( &threadId , NULL ,  alive_handler , (void*) &connfd) < 0)
        {
            perror("could not create alive  thread");
                    
            return 0;
        }        
        
        printf("wait for accept\n");
        connfd = accept(localListenfd, (struct sockaddr *)&cliAddr, (socklen_t*)&clilen); 
         
        // join the thread , so we don't terminate before the thread
        // pthread_join( threadId , NULL);        
    }    
    
    perror("error accept2");
        
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    using namespace std::chrono_literals;

    // Options
    bool foreground = true;

    // Service variables
    struct sigaction sa;
    int rc;
    
 
    int yes;
    int result;
   
 
    if (argc < 2)
    {
        printf("usage: %s can0 can1 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i;
    for (int i = 1; i < argc; i++)
    {
        strcpy(&(interface[i - 1][0]), argv[i]);
        numInterfaces++;
        printf("args: interface name: %s\n", &(interface[i - 1][0]));
    }

    // Check if the service should be run as a daemon
    if (!foreground) {
        if (::daemon(0, 1) == -1) {
            std::perror("daemon");
            return EXIT_FAILURE;
        }
    }

    // reg signal handlers
    sa.sa_handler = onSignal;
    ::sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    ::sigaction(SIGINT, &sa, nullptr);
    ::sigaction(SIGTERM, &sa, nullptr);
    ::sigaction(SIGQUIT, &sa, nullptr);
    ::sigaction(SIGHUP, &sa, nullptr);
    signalValue = 0;

    // Show start
    std::cout << "Started" << std::endl;

    /////////////////////////////////////////
    // server
    
    /*if((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("cannot create socket\n");
        return 0;
    }    
    
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5001);

    if(bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("cannot bind");
        return 0;
    }*/
    
    
    // client addr
    /*claddr.sin_family = AF_INET;
    claddr.sin_port = htons(5001);
    
    if (inet_aton("192.168.8.27" , &claddr.sin_addr) == 0) 
    {
        printf("inet_aton() failed\n");       
    }
    printf("init: claddr.sin_addr = %x\n", claddr.sin_addr);
    
    clientlen = sizeof(claddr);*/

    // TCP server    
    //connected = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));    

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5001); 
    
    // sock opts
    // disable nagle
    yes = 1;
    result = setsockopt(listenfd,
                        IPPROTO_TCP,
                        TCP_NODELAY,
                        (char *) &yes, 
                        sizeof(int));    // 1 - on, 0 - off
    //if (result < 0)
    // disable delayed ack
    yes = 1;
    result = setsockopt(listenfd,
                        TCP_QUICKACK,
                        TCP_NODELAY,
                        (char *) &yes, 
                        sizeof(int));    // 1 - on, 0 - off
    //if (result < 0)    
        


    int sockRet;
    // bind to sock
    sockRet = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    
    if (sockRet < 0)
    {
        perror("could not bind");
        return 0;
    }



    // start client accept thread
     if( pthread_create( &threadId , NULL ,  accept_handler , (void*) &listenfd) < 0)
    {
        perror("could not create client accept thread");
        return 0;
    }   
    
    
    // LED beagle
    #define BEAGLEBONE
    #ifdef BEAGLEBONE
    removeTrigger();
    
    fs.open (LED0_PATH "/brightness", std::fstream::out);
    fs << "1";
    fs.close();
    #endif
    
    // Main loop
    while (0 == signalValue) {
        sleep(1);       
    }

    std::cout << std::endl << "Exit" << std::endl;
    return EXIT_SUCCESS;

}
