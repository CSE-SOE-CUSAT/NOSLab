import socket,sys             
s = socket.socket()         
host = socket.gethostname()  #here you can specify ip address also
port = 12345                

try:
 s.connect((host, port)) 
 
 s.send('hello server');
 data = s.recv(1024);
 print data
except:
 print "EXCEPTION ",sys.exc_info()[0]
 raise
s.close()   



