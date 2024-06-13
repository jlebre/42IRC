#ifndef LIBS_HPP
# define LIBS_HPP

# include <iostream>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <cstring>
# include <cerrno>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <vector> 
# include <poll.h>
# include <sys/epoll.h>
# include <string>
# include <sys/select.h>
# include <sys/time.h>
# include <cstddef>
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <queue>
# include <exception>
# include <cstdlib>
# include <csignal>

# define BUF_SIZE		1024
# define MAX_CLIENTS	5
# define MAX_NICK_LENGTH 9
# define MAX_USER_LENGTH 10
# define MAX_REALNAME_LENGTH 50
# define MAX_CHANNEL_NAME_LENGTH 50
# define MAX_TOPIC_LENGTH 390
# define MAX_MESSAGE_LENGTH 512

#endif