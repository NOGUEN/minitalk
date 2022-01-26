FLAG=-Wall -Wextra -Werror

all:
	@gcc server.c utils.c -o server
	@gcc client.c utils.c -o client

clean:
	@rm -rf server client
fclean: clean
	@rm -rf server client
re: fclean all
