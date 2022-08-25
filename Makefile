# Output Name:
NAME:=			containers

# Folders:
BUILD:=			./build
SOURCE:=		./source

# Other Variables:
COMPILER:=		c++
COMPFLAGS:=		-Wall -Werror -Wextra -g -std=c++98

# Source Files:
SRCFILES:=\
		  main.cpp\

# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CXX:=		$(COMPILER)
CXXFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.cpp=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re test run

# Catch Rules
all:
	make -j $(nproc) $(NAME)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# Clean up Objects
clean:
	$(RM) -r $(BUILD)

# Clean up Executables and static libraries
fclean: clean
	$(RM) -r $(NAME)

# Clean the re-compile
re: fclean all

#Run the executable
run: re
	@echo "--------------------------------"
ifeq ($(OS),Linux)
	valgrind -q --leak-check=full --errors-for-leak-kinds=all $(NAME)
else ifeq ($(OS),Darwin)
	leaks -q --atExit -- $(NAME)
else
	$(NAME)
endif


