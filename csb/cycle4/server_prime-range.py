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
        i = 3
        list = [2]
        while (len(list) != int(data)): #main prime testing
            
            result = test_primality(i)
            if result:
                list.append(i) #if prime add to list
            i=i+1
        c.send(str(list))
    c.close()              
