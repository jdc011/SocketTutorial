# Compile the client and server
all:
	gcc server.c -o server
	gcc client.c -o client

# Compile the client and server with debugging option
debug:
	gcc server.c -o server -g
	gcc client.c -o client -g

# Remove the binary files
clean:
	rm client server
