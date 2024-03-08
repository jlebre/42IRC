FILE_NAME = main.cpp 

TEMPLATES_NAME = templates.tpp

TEMPLATES_DIR = templates

SRCS_DIR = srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(FILE_NAME)) \
	$(addprefix $(TEMPLATES_DIR)/, $(TEMPLATES_NAME))

CXX = g++

INC = -I includes/header.hpp

CXXFLAGS = -Wall -Wextra -Werror $(INC) -std=c++98

RM = rm -f

NAME = ircserv

all: $(NAME)

$(NAME): $(SRCS)
	@$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)
	@echo -e '[0;32m$(NAME) Compiled![0m'

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo -e '[0;31m$(NAME) Removed![0m'

re:
	@make fclean
	@make

a:
	@make re
	@make clean
	@./$(NAME) 80 password

.PHONY: all clean fclean re a
