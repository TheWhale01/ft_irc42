CXX= c++

NAME= ircserv

OBJ_DIR= obj/

DEP= ${SRCS:.cpp=.d}

SRC_DIR= src/

INCLUDES= includes/

CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98 -MMD

CFILES= $(addprefix $(SRC_DIR), main.cpp)

OBJS= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) 

fclean: clean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all

-include $(DEP)

.PHONY: all clean fclean re