NAME = graph

OBJDIR = obj
SRCDIR = .

SRCS = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.hpp)
CXX = c++
INCS = -I$(SRCDIR)
RM = rm -rf
MK = mkdir -p
TOUCH = touch

CXXFLAGS = -Wall -Wextra -Werror

LINKERS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
.DEFAULT_GOAL = all

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJS) $(LINKERS)

$(OBJDIR): | $(SRCDIR)
	$(MK) $@

all: $(OBJDIR) $(NAME)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re