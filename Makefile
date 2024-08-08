SRCDIR		= srcs/philo_bonus
SRCS		:= $(shell find $(SRCDIR) -name '*.c')

OBJDIR		= objs
OBJDIRS		= $(sort $(dir $(OBJS)))
OBJS		= $(subst $(SRCDIR)/,$(OBJDIR)/,$(subst .c,.o,$(SRCS)))

CWD			:= $(shell pwd)
HEADER_DIR	= philo
HEADERS		:= $(shell find $(HEADER_DIR) -name '*.h')
HEADERS_INC	= $(addprefix -I,$(sort $(dir $(HEADERS))))

ifeq ($(UNAME_S), Darwin)  # macos
	LINKERS	= 
else
	LINKERS	= -lpthread
endif

LIBS		= $(LIBFT) $(LINKERS)

IFLAGS		:= -I. $(HEADERS_INC)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3
AR			= ar -rcs
RM			= rm -rf
UP			= \033[1A
FLUSH		= \033[2K

NAME		= philo
ARGV		= 2 200 100 100 10


run: all
	./$(NAME) $(ARGV)

kill:
	kill $$(ps -A | grep $(NAME) | awk '{print $1}') 2> /dev/null

$(NAME): $(LIBS) $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LIBS) -o $(NAME)

all: $(NAME)

$(OBJDIRS):
	mkdir -p $@
	@echo "$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)"

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(TESTDIR)
	@$(RM) $(OBJDIRS)
	@$(RM) ./a.out

re: fclean $(NAME)

push:
	@echo -n "Commit name: "; read name; make fclean;\
	git add .; git commit -m "$$name"; git push;

BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
ifeq ($(BRANCH),HEAD)
BRANCH := main
endif
pull:
	git fetch --all
	git checkout -f $(BRANCH);
	git reset --hard origin/$(BRANCH);
	git submodule update --init --remote --recursive

.PHONY: all clean fclean re bonus push $(NAME)