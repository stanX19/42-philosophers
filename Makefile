BONUS_SRCDIR		= srcs/philo_bonus
BONUS_SRCS			:= $(shell find $(BONUS_SRCDIR) -name '*.c')

BONUS_OBJDIR		= objs/bonus
BONUS_OBJDIRS		= $(sort $(dir $(BONUS_OBJS)))
BONUS_OBJS			= $(subst $(BONUS_SRCDIR)/,$(BONUS_OBJDIR)/,$(subst .c,.o,$(BONUS_SRCS)))

BONUS_CWD			:= $(shell pwd)
BONUS_HEADER_DIR	= srcs/philo_bonus
BONUS_HEADERS		:= $(shell find $(BONUS_HEADER_DIR) -name '*.h')
BONUS_HEADERS_INC	= $(addprefix -I,$(sort $(dir $(BONUS_HEADERS))))

SRCDIR		= srcs/philo
SRCS		:= $(shell find $(SRCDIR) -name '*.c')

OBJDIR		= objs/philo
OBJDIRS		= $(sort $(dir $(OBJS)))
OBJS		= $(subst $(SRCDIR)/,$(OBJDIR)/,$(subst .c,.o,$(SRCS)))

CWD			:= $(shell pwd)
HEADER_DIR	= srcs/philo
HEADERS		:= $(shell find $(HEADER_DIR) -name '*.h')
HEADERS_INC	= $(addprefix -I,$(sort $(dir $(HEADERS))))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)  # macos
	LINKERS	:= 
else
	LINKERS	:= -lpthread
endif

LIBS		= $(LIBFT) $(LINKERS)

IFLAGS		:= -I. $(HEADERS_INC) $(BONUS_HEADERS_INC)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3
AR			= ar -rcs
RM			= rm -rf
UP			= \033[1A
FLUSH		= \033[2K

NAME		= philo
BONUS_NAME	= philo_bonus
ARGV		= 2 200 100 100


run: all
	./$(NAME) $(ARGV)

kill:
	kill $$(ps -A | grep $(NAME) | awk '{print $1}') 2> /dev/null

$(NAME): $(LIBS) $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LIBS) -o $(NAME)

$(BONUS_NAME): $(LIBS) $(BONUS_OBJDIRS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(IFLAGS) $(LIBS) -o $(BONUS_NAME)

all: $(NAME) $(BONUS_NAME)

$(OBJDIRS) $(BONUS_OBJDIRS):
	mkdir -p $@
	@echo "$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)"

$(BONUS_OBJDIR)/%.o: $(BONUS_SRCDIR)/%.c $(BONUS_HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)$(FLUSH)$(UP)"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	@$(RM) $(TESTDIR)
	@$(RM) $(OBJDIRS) $(BONUS_OBJDIRS)
	@$(RM) $(NAME) $(BONUS_NAME) ./a.out

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