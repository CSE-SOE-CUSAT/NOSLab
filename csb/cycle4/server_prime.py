import socket
s = socket.socket()        
host = socket.gethostname()  
port = 12345              
print "host ",host
s.bind((host, port))     

s.listen(5)  
def test_primality(n):    
    n = int(n)
    if n <= 1:
        return False
    elif n <= 3 :
        return True
    elif n%2 == 0 or n%3 == 0 :
        return False
    i = 5
   
    while ( i*i <= n):
        #print "Inside while"
        if (n % i == 0 or n%(i+2)==0):
            return False
        i+=6
    return True
                   
while True:
    c, addr = s.accept()    
    print 'Got connection from',addr
    while True:
        data = c.recv(4);
        if not data:
            break
        result = str(test_primality(data))
        c.send(result)
    c.close()              
