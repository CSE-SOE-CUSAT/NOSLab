import socket                                         
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
host = socket.gethostname()                           
port = 1743                                      
serversocket.bind((host, port))                                  
serversocket.listen(50)                                           
while True:
	# establish a connection
	clientsocket,addr = serversocket.accept()
	ar = clientsocket.recv(1024)	
	print("%s" % ar.decode('ascii'))
	

