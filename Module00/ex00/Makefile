NAME = bank

OBJDIR = obj
SRCDIR = .

SRCS = ./main.cpp ./Account.cpp ./Bank.cpp
HEADERS = $(wildcard $(SRCDIR)/*.hpp)
CXX = c++
INCS = -I$(SRCDIR)
RM = rm -rf
MK = mkdir -p

CXXFLAGS = -Wall -Wextra -Werror

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
.DEFAULT_GOAL = all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJS)

$(OBJDIR): | $(SRCDIR)
	$(MK) $@

all: $(OBJDIR) $(NAME)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re