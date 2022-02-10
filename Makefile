FLAG = -Wall -Wextra -Werror

all:
	@gcc $(FLAG) server.c utils.c exit.c -o server
	@gcc $(FLAG) client.c utils.c exit.c -o client

clean:
	@rm -rf server client
	@rm -rf server_bonus client_bonus

fclean: clean
	@rm -rf server client
	@rm -rf server_bonus client_bonus

re: fclean all

bonus: dummy
	@gcc $(FLAG) bonus/server_bonus.c exit.c utils.c -o server_bonus
	@gcc $(FLAG) bonus/client_bonus.c exit.c utils.c -o client_bonus

dummy:
