import socket,sys             
s = socket.socket()         
host = socket.gethostname()  #here you can specify ip address also
port = 12345                

try:
 s.connect((host, port)) 
 while (1):
         input_no = raw_input("Enter the no for primality check\n")
         if not input_no:
                 break
         s.send(str(input_no));
         data = s.recv(1024);
         if data=="True":
                 print "It is a prime\n"
         else:
                 print "It's not a prime \n"
except:
 print "EXCEPTION ",sys.exc_info()[0]
 raise
s.close()   



