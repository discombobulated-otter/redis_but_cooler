import socket

s = socket.socket()
s.connect(("127.0.0.1", 6379))

s.sendall(b"*3\r\n$3\r\nSET\r\n$1\r\na\r\n$3\r\n123\r\n")
print(s.recv(1024))

s.sendall(b"*2\r\n$3\r\nGET\r\n$1\r\na\r\n")
print(s.recv(1024))

