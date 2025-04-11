NAME			=	minitalk
CLIENT			=	client
SERVER			=	server
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

all:			$(NAME)

$(NAME): $(SERVER) $(CLIENT)

${CLIENT}:		ft_client.c
				${CC} ${CFLAGS} -o client ft_client.c

${SERVER}:		ft_server.c
				${CC} ${CFLAGS} -o server ft_server.c
	
clean:
				$(RM) $(SERVER) $(CLIENT)

fclean:			clean

re:				clean all

.PHONY:			all $(NAME) clean fclean re
