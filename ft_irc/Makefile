SRCS = main.cpp classes/Client/client.cpp classes/Client/info.cpp \
		classes/Server/server.cpp classes/Server/main_loop.cpp \
		classes/Server/connect.cpp classes/Server/reply.cpp \
		classes/Server/process_input.cpp classes/Server/parser.cpp \
		classes/Server/delete_all.cpp \
		commands/pass.cpp commands/nick.cpp \
		commands/user.cpp commands/join.cpp \
		commands/part.cpp commands/quit.cpp \
		commands/privmsg.cpp commands/mode.cpp \
		commands/topic.cpp commands/kick.cpp \
		commands/invite.cpp \
		classes/Channel/channel.cpp classes/Channel/info.cpp \
		classes/Socket/socket.cpp classes/Socket/read.cpp \
		classes/Socket/poll.cpp 

CXX = c++

INC = -I includes -I classes/Client -I classes/Server -I classes/Channel

CXXFLAGS = -Wall -Wextra -Werror $(INC) -std=c++98

RM = rm -f

NAME = ircserv

all: $(NAME)

$(NAME): $(SRCS)
	@$(CXX) $(CXXFLAGS) -s $(SRCS) -o $(NAME)
	@echo -e '[0;32m$(NAME) Compiled![0m'

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo -e '[0;31m$(NAME) Removed![0m'

re:
	@make -s fclean && make

a:
	@make -s re && ./$(NAME) 6667 hello

.PHONY: all clean fclean re a
