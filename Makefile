CXX= c++

NAME= ircserv
OBJ_DIR= obj/
DEP_DIR= dep/
SRC_DIR= src/
INCLUDES= includes/

SRCS= $(addprefix $(SRC_DIR), main.cpp Server.cpp Channel.cpp Client.cpp cmd/authentication.cpp \
	utils.cpp cmd/cap.cpp exceptions/exception.cpp exceptions/NeedMoreParamsException.cpp \
	exceptions/UnknownCommandException.cpp exceptions/NoNickNameGivenException.cpp \
	exceptions/ErroneusNickNameException.cpp exceptions/NickNameInUseException.cpp \
	exceptions/AlreadyRegistredException.cpp cmd/quit.cpp cmd/channel_user.cpp cmd/message.cpp\
	)
DEP= $(patsubst $(SRC_DIR)%.cpp, $(DEP_DIR)%.d, $(SRCS))
OBJS= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(subst $(OBJ_DIR), $(DEP_DIR), $(dir $@))
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(patsubst $(OBJ_DIR)%.o, $(DEP_DIR)%.d, $@) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re