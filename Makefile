CXX= c++

NAME= ircserv
OBJ_DIR= obj/
DEP_DIR= dep/
SRC_DIR= src/
INCLUDES= includes/

SRCS= $(addprefix $(SRC_DIR), main.cpp)
OBJS= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(DEP_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(patsubst $(OBJ_DIR)%.o, $(DEP_DIR)%.d, $@) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re