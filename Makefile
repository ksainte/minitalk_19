# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksainte <ksainte@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 22:55:58 by ksainte           #+#    #+#              #
#    Updated: 2024/05/21 13:04:02 by ksainte          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_BONUS_SRCS = client_bonus.c
SERVER_BONUS_SRCS = server_bonus.c
LIBFT_PATH = Libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -L$(LIBFT_PATH) -lft

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_BONUS_SRCS) -L$(LIBFT_PATH) -lft

$(SERVER_BONUS_NAME): $(SERVER_BONUS_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_BONUS_SRCS) -L$(LIBFT_PATH) -lft

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

.PHONY: all clean fclean re bonus

#Dependencies and Executables:

    #$(CLIENT_NAME), $(SERVER_NAME): Dependencies include respective source files (client.c, server.c) and libft.a archive. =>It COMPILES each source with the specified flags and LINKS against libft to produce an executable ie a compiled binary.

#Libraries:

    #LIBFT_PATH: Path to the libft directory.
    #LIBFT_ARCHIVE: Path to libft.a archive within libft directory.
    #$(LIBFT_ARCHIVE): Builds the libft.a archive by invoking the makefile inside the libft directory.

#Specifically:
#$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE): This line defines a target named $(CLIENT_NAME). This target depends on $(CLIENT_SRCS) (source files for the client program) and $(LIBFT_ARCHIVE) (the compiled library libft.a).
#This means that before attempting to build the client program, Make will ensure that these dependencies are up to date.

#in $(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft:
#-o $@: This flag specifies the output file name. $@ is a special variable that represents the target name ($(CLIENT_NAME) in this case). 
# ==> So, this flag tells the compiler to output the compiled binary as $(CLIENT_NAME).

        
#-L$(LIBFT_PATH): This flag tells the linker to search for libraries in the directory specified by $(LIBFT_PATH).
#-lft: This flag links against a library named libft.a The -l flag is followed by the name of the library without the lib prefix and the file extension. This tells the linker to link against the specified library (libft.a in this case).
#In summary, these lines compile the client program by invoking the C compiler ($(CC)), passing it source files ($(CLIENT_SRCS)), compiler flags ($(CFLAGS)), and linking against the libft library (-L$(LIBFT_PATH) -lft). The compiled binary is named $(CLIENT_NAME).

#Why not .o?
# you can modify the Makefile to compile each source file separately into an object file and then link them together.

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_BONUS_SRCS = client_bonus.c
SERVER_BONUS_SRCS = server_bonus.c
LIBFT_PATH = Libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFT_PATH) -lft

$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) -L$(LIBFT_PATH) -lft

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_BONUS_OBJS) -L$(LIBFT_PATH) -lft

$(SERVER_BONUS_NAME): $(SERVER_BONUS_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_BONUS_OBJS) -L$(LIBFT_PATH) -lft

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_BONUS_OBJS) $(SERVER_BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

.PHONY: all clean fclean re bonus

#What I dont understand is that normally an executable must be linked to object files to execute them, that is what we do here :  $(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFT_PATH) -lft. 
#How come this line of code works too : $(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft?
#=>However, the key point here is that GCC (or most C compilers) can handle both compiling and linking in a single step if you provide it with source files directly.

#When you pass source files directly to the compiler instead of object files, GCC goes through several stages:

 #   Preprocessing: The compiler preprocesses the source files, handling directives like #include, #define, and removing comments.

 #   Compilation: It compiles each source file into its corresponding object file (client.o, server.o) WITHOUT PERFORMING the final linking stage.

 #   Linking: Finally, GCC performs the LINKING stage, where it links the object files together along with any specified libraries (-lft in this case) to produce the FINAL EXECUTABLE.
 

# The pattern rule:

#makefile

# %.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

#Tells make how to convert any .c file into a .o file using the specified compiler and flags, ensuring consistent and automated compilation of source files into object files.

# -c: This flag tells the compiler to compile the source file into an object file WITHOUT LINKING.

# $<: This is an automatic variable in make that represents the first prerequisite (the .c file in this case).

# -o $@: This flag specifies the output filename. $@ is an automatic variable representing the target (the .o file).

#LINKING IS DONE AT THIS STAGE : $(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFT_PATH) -lft, between the executable, the client.o object and libft.a that represents .o's of the whole Libft directory...

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#IN SUMMARY

#in $(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_ARCHIVE)
#	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFT_PATH) -lft

#The first line build the necessary object lines to compute the next line
#The $(CLIENT_OBJS) makes Makefile know it needs to build $(CLIENT_SRCS:.c=.o) which is client.o
#IT looks for a rule to build .o files and finds out %.o: %.c which tells it it needs it corresponding clients.c file present in the directory
#IF there is one, it compiles with flags the .c file and creates an object file .o (without linking) named after %.o
#IF everything went smooth, it compiles the binary by linking it to compiled object files client.o AND to the compiled library refering to it .a
#libft.a : A static library is an archive of object files. It allows you to bundle multiple object files into a single file (.a file) that can be linked with other programs.
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
