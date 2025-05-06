NAME_CLIENT = client
NAME_SERVER = server
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Chemins des répertoires
SRC_DIR = src/
INC_DIR = include/
LIBFT_DIR = Libft/
LIBFT_INC = $(LIBFT_DIR)includes/

# Sources et objets
CLIENT_SRC = $(SRC_DIR)client.c
SERVER_SRC = $(SRC_DIR)server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Headers
HEADER = $(INC_DIR)minitalk.h

# Libft
LIBFT = $(LIBFT_DIR)libft.a

# Flags d'inclusion
INCLUDES = -I$(INC_DIR) -I$(LIBFT_INC)

# Règle par défaut
all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

# Compilation des objets
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la Libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compilation du client
$(NAME_CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

# Compilation du serveur
$(NAME_SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(SERVER_OBJ) -L$(LIBFT_DIR) -lft

# Nettoyage des objets
clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)
	@make clean -C $(LIBFT_DIR)

# Nettoyage complet
fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	@make fclean -C $(LIBFT_DIR)

# Recompilation complète
re: fclean all

# Règle pour ne pas que les noms de fichiers interfèrent
.PHONY: all clean fclean re