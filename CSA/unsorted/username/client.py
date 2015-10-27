import socket
from heapq import heappush, heappop, heapify
from collections import defaultdict
##defbig
def encode(symb2freq):
    """Huffman encode the given dict mapping symbols to weights"""
    heap = [[wt, [sym, ""]] for sym, wt in symb2freq.items()]
    heapify(heap)
    while len(heap) > 1:
        lo = heappop(heap)
        hi = heappop(heap)
        for pair in lo[1:]:
            pair[1] = '1' + pair[1]
        for pair in hi[1:]:
            pair[1] = '0' + pair[1]
        heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:])
    return sorted(heappop(heap)[1:], key=lambda p: (len(p[-1]), p))
##defend
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
host = socket.gethostname()                           
port = 1743
s.connect((host, port))                               
s.send("#BEGIN")
s.send("!")
f = open('a.txt', 'r')

#for line in f.readlines():
txt = 'mississippi river'
symb2freq = defaultdict(int)
for ch in txt:
	symb2freq[ch] += 1
huff = encode(symb2freq)
for p in huff:
	s.send("{0},{1},{2}".format(p[0], symb2freq[p[0]], p[1]))
s.send("#END")
s.close()


##############3/////////////



 

