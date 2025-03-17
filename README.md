# 🌍 42IRC - IRC Server

![IRC Logo](https://upload.wikimedia.org/wikipedia/commons/6/69/Internet_Relay_Chat_logo.png)

## 📚 Introduction

### 💬 What is IRC?
Internet Relay Chat (IRC) is a protocol for real-time text communication. It allows:

✔ **Channels**: Chat rooms prefixed with `#` (e.g., `#example`)

✔ **Private Messages**: Direct conversations between users

✔ **Nicknames**: Unique identifiers for each user

✔ **Servers and Networks**: Users connect to an IRC server, which may be part of a larger network

---

## ⚙️ Configuration

### 🧑‍🔧 Server Installation
To test the IRC server, use **HexChat** or another IRC client.

```sh
git clone https://www.github.com/jlebre/42IRC.git
cd 42IRC/ft_irc
make a
```
📌 **`make a`**: Removes old files, compiles the program, and runs it on port `6667` with password `hello`.

---

## 📌 Allowed Functions
This project utilizes several system functions:

- 🤧 **socket()** → Creates a socket
- 📍 **bind()** → Binds the socket to an IP and port
- 🎧 **listen()** → Prepares the socket to accept connections
- 🤝 **accept()** → Accepts client connections
- ✉ **send()/recv()** → Sends and receives data
- 🚦 **poll()/epoll()** → Ensures efficient connection management

---

## 🚀 Server Setup

### 🔹 Main Function
```cpp
int main(int argc, char **argv) {
    Server irc;
    irc.parse(argc, argv);
    return 0;
}
```

### 🔹 Socket Initialization
```cpp
void Server::init_socket() {
    _sock.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
    if (_sock.fd == -1) {
        std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
        exit(1);
    }
}
```

---

## ⚡ Connection Management with EPOLL
EPOLL is used for efficient handling of multiple connections.

```cpp
void Server::init_poll() {
    _event.events = EPOLLIN | EPOLLOUT;
    _event.data.fd = _sock.fd;
    event_fd = epoll_create1(0);
    epoll_ctl(event_fd, EPOLL_CTL_ADD, _sock.fd, &_event);
}
```

---

## 📌 Class Structure

### 🖥️ **Server**
Manages connections and commands

### 👤 **Client**
Stores user information (nickname, connection state)

### 🔹 **Channel**
Represents an IRC channel, managing users and messages

---

## Commands 🎮

The protocol for each command follows a standard procedure:

✅ Verify if the client is registered. If not, send reply 451.

📌 Separate the command and its arguments.

🔄 Apply the necessary changes to all relevant members.

### 🎫 INVITE
**Usage:** `/invite <nick> <#channel>`

Server Considerations: Validate permissions, check if the channel exists.

Server-to-Client Message: `:server_name INVITE invited_user :channel_name`

### 🛋 JOIN
**Usage:** `/join <#channel>`

Server Considerations: Validate channel existence and permissions.

Server-to-Client Message: `:user!user@host JOIN :#channel`

### 🧑‍🛠️ KICK
**Usage:** `/kick <#channel> <nick> [<reason>]`

Server Considerations: Validate privileges, notify affected users.

Server-to-Client Message: `:server_name KICK channel_name kicked_user :reason`

### 🌐 MODE
**Usage:** `/mode <#channel> <mode> [<mode params>]`

Server Considerations: Validate mode changes.

Server-to-Client Message: `:server_name MODE target parameters`

### 🔄 NICK
**Usage:** `/nick <newnick>`

Server Considerations: Ensure uniqueness, notify users.

Server-to-Client Message: `:old_nick NICK new_nick`

### 👣 PART
**Usage:** `/part <#channel> [<message>]`

Server Considerations: Validate if user is in the channel.

Server-to-Client Message: `:user!user@host PART #channel`

### 🔑 PASS
**Usage:** `/pass <password>`

Server Considerations: Authenticate users.

Server-to-Client Message: None.

### ✉ PRIVMSG
**Usage:** `/privmsg <target> <message>`

Server Considerations: Deliver messages appropriately.

Server-to-Client Message: `:sender PRIVMSG target :message_text`

### ❌ QUIT
**Usage:** `/quit [<message>]`

Server Considerations: Notify users of disconnection.

Server-to-Client Message: `:user!user@host QUIT :Quit message`

### 📝 TOPIC
**Usage:** `/topic <#channel> [<newtopic>]`

Server Considerations: Validate topic changes, notify users.

Server-to-Client Message: `:server_name TOPIC #channel :new_topic`

### 🆕 USER
**Usage:** `/user <username> <hostname> <servername> <realname>`

Server Considerations: Authenticate user, set initial attributes.

Server-to-Client Message: None.

---

## 🎮 Important Links and Files

[IRC Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)

[IRC Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)

[IRC Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)

---

This document summarizes the main functionalities of the **IRC Server** and its implementation. For more details, refer to the repository files! 🚀

---

![image](https://github.com/user-attachments/assets/47c8da6b-23b0-42f2-8570-3f46049e627f)


