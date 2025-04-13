
Important functions and what they do:
getaddrinfo(): Resolves a hostname and service into a list of address structures, preparing the necessary info (IP, port, protocol) for creating a socket.

socket(): Creates a new socket and returns its file descriptor, which acts like a handle used for all future socket operations.

bind(): Associates the socket with a specific IP address and port number on the local machine.

connect(): Initiates a connection from a client socket to a server specified by an address.

listen(): Marks a bound socket as passive, meaning it will be used to accept incoming connection requests.

accept(): Accepts an incoming connection on a listening socket and returns a new socket for communicating with the client.

send() and recv(): Used to send data to and receive data from a connected socket, enabling actual communication.
