NAME = WorkshopSystem

OBJDIR = obj
SRCDIR = .

SRCS = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.hpp)
CXX = c++ -std=c++98
INCS = -I$(SRCDIR)
RM = rm -rf
MK = mkdir -p
TOUCH = touch

CXXFLAGS = -Wall -Wextra -Werror


OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
.DEFAULT_GOAL = all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
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