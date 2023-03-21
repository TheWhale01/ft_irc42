CXX= c++

NAME= ircserv

OBJ_DIR= obj/

DEP_DIR= dep/

SRC_DIR= src/

INCLUDES= includes/

DEP= $(patsubst $(SRC_DIR)%.cpp, $(DEP_DIR)%.d, $(SRCS_DIR))

CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98 -MMD

CFILES= $(addprefix $(SRC_DIR), main.cpp)

OBJS= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(DEP_DIR)

re: fclean
	$(MAKE) all

-include $(DEP)

.PHONY: all clean fclean re