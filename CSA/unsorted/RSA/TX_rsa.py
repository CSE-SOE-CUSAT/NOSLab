import random
import socket
from collections import namedtuple

def get_primes(start, stop):
    if start >= stop:
        return []
    primes = [2]
    for n in range(3, stop + 1, 2):
        for p in primes:
            if n % p == 0:
                break
        else:
            primes.append(n)
    while primes and primes[0] < start:
        del primes[0]
    return primes

def are_relatively_prime(a, b):
    for n in range(2, min(a, b) + 1):
        if a % n == b % n == 0:
            return False
    return True

def make_key_pair(length):
    if length < 4:
        raise ValueError('cannot generate a key of length less '
                         'than 4 (got {!r})'.format(length))
    n_min = 1 << (length - 1)
    n_max = (1 << length) - 1
    start = 1 << (length // 2 - 1)
    stop = 1 << (length // 2 + 1)
    primes = get_primes(start, stop)
    while primes:
        p = random.choice(primes)
        primes.remove(p)
        q_candidates = [q for q in primes
                        if n_min <= p * q <= n_max]
        if q_candidates:
            q = random.choice(q_candidates)
            break
    else:
        raise AssertionError("cannot find 'p' and 'q' for a key of "
                             "length={!r}".format(length))
    stop = (p - 1) * (q - 1)
    for e in range(3, stop, 2):
        if are_relatively_prime(e, stop):
            break
    else:
        raise AssertionError("cannot find 'e' with p={!r} "
                             "and q={!r}".format(p, q))
    for d in range(3, stop, 2):
        if d * e % stop == 1:
            break
    else:
        raise AssertionError("cannot find 'd' with p={!r}, q={!r} "
                             "and e={!r}".format(p, q, e))
    return PublicKey(p * q, e), PrivateKey(p * q, d)

class PublicKey(namedtuple('PublicKey', 'n e')):
    __slots__ = ()
    def encrypt(self, x):
        return pow(x, self.e, self.n)

class PrivateKey(namedtuple('PrivateKey', 'n d')):
    __slots__ = ()
    def decrypt(self, x):
        return pow(x, self.d, self.n)

if __name__ == '__main__':
	sa = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
	sb = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
	sc = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
	host = socket.gethostname()                           
	porta = 8000
	portb = porta + 1
	portc = portb + 1
	sa.connect((host, porta))
	msga = sa.recv(1024)
	sa.close()
	sb.connect((host, portb))
	msgb = sb.recv(1024)
	sb.close()
	sc.connect((host, portc))		
	public = PublicKey(n=int(msgb), e=int(msga))	
	print public.encrypt(ord('Z'))
	sc.send(str( public.encrypt(ord('Z'))))
	sc.close()
	
