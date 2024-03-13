FILE_NAME = main.cpp parser.cpp \
		commands.cpp utils.cpp start.cpp

TEMPLATES_NAME = templates.tpp

TEMPLATES_DIR = templates

SRCS_DIR = srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(FILE_NAME)) \
	$(addprefix $(TEMPLATES_DIR)/, $(TEMPLATES_NAME))

CXX = c++

INC = -I includes

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
	@make -s re && ./$(NAME) 2000 hello

.PHONY: all clean fclean re a
