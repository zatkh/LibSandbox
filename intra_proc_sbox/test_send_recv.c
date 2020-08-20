#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "nlink.h"


int send_recv_msg(char* message) {

int fd;
struct iovec iov;
struct nlmsghdr *nlh = NULL;
struct sockaddr_nl src_addr;
struct msghdr msg;
struct sockaddr_nl dest_addr;
 int ret=0;

 fd = socket(PF_NETLINK, SOCK_RAW,NETLINK_USER);

 memset(&src_addr, 0, sizeof(src_addr));
 src_addr.nl_family = AF_NETLINK;
 src_addr.nl_pid = getpid();  /* self pid */
 src_addr.nl_groups = 0;  /* not in mcast groups */
 bind(fd, (struct sockaddr*)&src_addr,
      sizeof(src_addr));

 memset(&dest_addr, 0, sizeof(dest_addr));
 dest_addr.nl_family = AF_NETLINK;
 dest_addr.nl_pid = 0;   /* For Linux Kernel */
 dest_addr.nl_groups = 0; /* unicast */

 nlh=(struct nlmsghdr *)malloc(
		         NLMSG_SPACE(MAX_PAYLOAD));

 nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
 nlh->nlmsg_pid = getpid();  /* self pid */
 nlh->nlmsg_flags = 0;

 strncpy(NLMSG_DATA(nlh), message,strlen(message));

 iov.iov_base = (void *)nlh;
 iov.iov_len = nlh->nlmsg_len;
 msg.msg_name = (void *)&dest_addr;
 msg.msg_namelen = sizeof(dest_addr);
 msg.msg_iov = &iov;
 msg.msg_iovlen = 1;

 sendmsg(fd, &msg, 0);

 /* Read message from kernel */
 memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
 recvmsg(fd, &msg, 0);
 printf(" Received message payload: %s\n",
	NLMSG_DATA(nlh));

 ret=(atoi((char*)NLMSG_DATA(nlh)));
 // printf("ret test:%d\n",ret);

 /* Close Netlink Socket */
 close(fd);
 return ret;
}

int main(void) {
//int retval=0;
  
send_recv_msg("memdom,create");
send_recv_msg("memdom,create");


}