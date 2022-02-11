NAME = minitalk
NAME_BONUS = minitalk_bonus

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus	

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): server client
		
server:
	@gcc $(FLAG) server.c utils.c exit.c -o $(SERVER)

client:
	@gcc $(FLAG) client.c utils.c exit.c -o $(CLIENT)

clean:
	@rm -rf server client
	@rm -rf server_bonus client_bonus

fclean: clean
	@rm -rf server client
	@rm -rf server_bonus client_bonus

re: fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS): server_bonus client_bonus

server_bonus:
	@gcc $(FLAG) bonus/server_bonus.c exit.c utils.c -o $(SERVER_BONUS)

client_bonus:
	@gcc $(FLAG) bonus/client_bonus.c exit.c utils.c -o $(CLIENT_BONUS)
