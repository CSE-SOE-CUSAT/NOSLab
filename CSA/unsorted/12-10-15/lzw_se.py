import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
port=8886
s.bind(('localhost',port))
s.listen(50)
print "Server started to listen to listen on port ", port
def compress(uncompressed):
    """Compress a string to a list of output symbols."""
 
    # Build the dictionary.
    dict_size = 256
    dictionary = dict((chr(i), chr(i)) for i in xrange(dict_size))
    # in Python 3: dictionary = {chr(i): chr(i) for i in range(dict_size)}
 
    w = ""
    result = []
    for c in uncompressed:
        wc = w + c
        if wc in dictionary:
            w = wc
        else:
            result.append(dictionary[w])
            # Add wc to the dictionary.
            dictionary[wc] = dict_size
            dict_size += 1
            w = c
 
    if w:
        result.append(dictionary[w])
    return result
 
 
def decompress(compressed):
    """Decompress a list of output ks to a string."""
    from cStringIO import StringIO
 
    dict_size = 256
    dictionary = dict((chr(i), chr(i)) for i in xrange(dict_size))

    result = StringIO()
    w = compressed.pop(0)
    result.write(w)
    for k in compressed:
        if k in dictionary:
            entry = dictionary[k]
        elif k == dict_size:
            entry = w + w[0]
        else:
            raise ValueError('Bad compressed k: %s' % k)
        result.write(entry)
 
        dictionary[dict_size] = w + entry[0]
        dict_size += 1
 
        w = entry
    return result.getvalue()
while True:
	clientsocket,address=s.accept()
	print "Connected with",address
	data=clientsocket.recv(2048)
	print data
	print("%s" % data.decode('ascii'))
	s.close()	

