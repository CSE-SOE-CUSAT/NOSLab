import socket               

s = socket.socket()        
host = socket.gethostname()  
port = 12345               
print "host ",host
s.bind((host, port))     

s.listen(5)                 
while True:
   c, addr = s.accept()    
   print 'Got connection from',addr
   data = c.recv(1024);
   print 'data  ',data;
   c.send('Thank you for connecting')
   c.close()              
