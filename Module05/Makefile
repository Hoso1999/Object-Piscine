NAME = transportSystem

ROOT = .
SRCDIR = src
CONFDIR = conf
INCDIR = include
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
DEPSDIR = $(BUILDDIR)/deps

SRCS = $(wildcard $(SRCDIR)/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.cpp, $(DEPSDIR)/%.d, $(SRCS))

.DEFAULT_GOAL = all

MK = mkdir -p
RM = rm -rf
CXX = g++ -std=c++17 -g
DEFINES = -DCONFDIR=\"$(CONFDIR)\"
CXXFLAGS = $(DEFINES)
INCS = -I$(INCDIR) -I$(ROOT)

$(DEPSDIR): $(SRCDIR)
	$(MK) $@

$(OBJDIR): $(SRCDIR)
	$(MK) $@

$(BUILDDIR): $(SRCDIR)
	$(MK) $@

$(DEPSDIR)/%.d: $(SRCDIR)/%.cpp | $(DEPSDIR)
	@set -e; $(RM) $@; \
	$(CXX) -M $(CXXFLAGS) $(INCS) $< | \
	sed "s/\($*\)\.o[ :]*/\1.o $@ : /g" > $@; \
	[ -s $@ ] || $(RM) $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCS) -MMD -MP -c $< -o $@

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCS) $^ -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BUILDDIR)

re: fclean all

.PHONY: all clean fclean re