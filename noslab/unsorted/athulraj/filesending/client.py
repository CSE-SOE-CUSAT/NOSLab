import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
host = socket.gethostname()                           
port = 1743
s.connect((host, port))                               
f = open('a.png', 'r')
s.send(f.read())
s.close()

