# push_win.py
import socket, sys

HOST = "192.168.1.197"
PORT = 9000
FILE = sys.argv[1]

s = socket.socket()
s.connect((HOST, PORT))

with open(FILE, "rb") as f:
    while chunk := f.read(1 << 25):
        s.sendall(chunk)

s.close()


