FLAG=-Wall -Wextra -Werror

all:
	@gcc server.c utils.c exit.c -o server
	@gcc client.c utils.c exit.c -o client

clean:
	@rm -rf server client
fclean: clean
	@rm -rf server client
re: fclean all
