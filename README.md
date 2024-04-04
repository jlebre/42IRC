# 42IRC
This project is about creating an IRC server.

Using HexChat (an actual IRC client) to connect to the server and test it.

Internet is ruled by solid standards protocols that allow connected computers to interact with each other.

It’s always a good thing to know.

## Setup

## What is an IRC

#

## Step by step
# Setup Server Socket
```cpp
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(6667); // Listen on port 6667
serverAddr.sin_addr.s_addr = INADDR_ANY;
bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
listen(sockfd, 10); // Listen for up to 10 connections
```