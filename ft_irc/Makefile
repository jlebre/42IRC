#FILE_NAME = srcs/main.cpp Client/client.cpp \
		srcs/commands.cpp srcs/utils.cpp \
		srcs/handle_fd.cpp srcs/main_loop.cpp \
		srcs/socket.cpp Channel/channel.cpp \
		Server/server.cpp Socket/socket.cpp 

#TEMPLATES_NAME = templates.tpp

#TEMPLATES_DIR = templates

#SRCS_DIR = srcs

#SRCS = $(addprefix $(SRCS_DIR)/, $(FILE_NAME)) \
	$(addprefix $(TEMPLATES_DIR)/, $(TEMPLATES_NAME))

SRCS = srcs/main.cpp Client/client.cpp Client/info.cpp \
		Server/server.cpp Server/main_loop.cpp \
		Server/connect.cpp Server/execute.cpp \
		Server/process_input.cpp Server/parser.cpp \
		Server/reply.cpp \
		Commands/pass.cpp Commands/nick.cpp \
		Commands/user.cpp Commands/join.cpp \
		Commands/part.cpp Commands/quit.cpp \
		Commands/privmsg.cpp Commands/mode.cpp \
		Commands/topic.cpp Commands/kick.cpp \
		Commands/invite.cpp \
		Channel/channel.cpp Channel/info.cpp \
		Socket/socket.cpp Socket/read.cpp \
		Socket/poll.cpp 

CXX = c++

INC = -I includes -I Client -I Server -I Channel

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
