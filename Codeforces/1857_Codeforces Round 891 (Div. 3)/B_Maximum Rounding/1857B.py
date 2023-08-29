########################## IMPORTS ####################################
import os, sys, math, cmath, operator as op

from functools import reduce
from io import BytesIO,IOBase
from collections import Counter

#---------------------------- MAIN CODE -----------------------------#
def solve():
    best=x=inp()
    y = 1
    while(y<x):
        q = (x//y)%10
        if(q<5): x -= q*y
        else: x += (10-q)*y
        y*=10
        best=max(best,x)
    print(best)

#---------------------------- END CODE -----------------------------#



# ''' # REGION FASTIO   1.7 sec average INTEST 
BUFSIZ=8192
class FastIO(IOBase):
    newlines=0
    def __init__(self,file):
        self._fd=file.fileno()
        self.buffer=BytesIO()
        self.writable="n"in file.mode or "r" not in file.mode # type: ignore
        self.write=self.buffer.write if self.writable else None # type: ignore
    def read(self):
        while True:
            b=os.read(self._fd,max(os.fstat(self._fd).st_size,BUFSIZ))
            if not b:
                break
            ptr=self.buffer.tell()
            _=self.buffer.seek(0,2),self.buffer.write(b),self.buffer.seek(ptr)
        self.newlines=0
        return self.buffer.read()
    def readline(self):
        while self.newlines==0:
            b=os.read(self._fd,max(os.fstat(self._fd).st_size, BUFSIZ))
            self.newlines=b.count(b"\n")+(not b)
            ptr=self.buffer.tell()
            _=self.buffer.seek(0, 2),self.buffer.write(b),self.buffer.seek(ptr)
        self.newlines-=1
        return self.buffer.readline()
    def flush(self):
        if self.writable:
            os.write(self._fd,self.buffer.getvalue())
            _=self.buffer.truncate(0),self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer=FastIO(file)
        self.flush=self.buffer.flush
        self.writable=self.buffer.writable
        self.write=lambda s:self.buffer.write(s.encode("ascii"))
        self.read=lambda:self.buffer.read().decode("ascii")
        self.readline=lambda:self.buffer.readline().decode("ascii") # type: ignore
if sys.version_info[0]<3:
    sys.stdin,sys.stdout=FastIO(sys.stdin),FastIO(sys.stdout)
else:
    sys.stdin,sys.stdout=IOWrapper(sys.stdin),IOWrapper(sys.stdout)
input=lambda:sys.stdin.readline().rstrip("\r\n")
inp = lambda: int(input())
invr = lambda: map(int,input().split())
invrs = lambda: map(lambda x: x, input().split())
infn = lambda fn: map(fn, input().split())
inlt = lambda: list(map(int, input().split()))
inlts = lambda: list(input())
def print_rev(seq, sep = '', end = '') -> None:
    for i in range(len(seq)): print(seq[~i], sep = sep, end = end)
def print_yn(value: bool, **kwargs) -> None: 
    print(("NO", "YES")[value], **kwargs)
#---------------------------- REGION END --------------------------#

#------------------------------ Funcs -----------------------------#
#                                                                  #
#            https://github.com/cheran-senthil/PyRival             #
#                                                                  #
########################## GCD/LCM #################################
gcd = math.gcd

def extended_gcd(a, b):
    """returns gcd(a, b), s, r s.t. a * s + b * r == gcd(a, b)"""
    s, old_s = 0, 1
    r, old_r = b, a
    while r:
        q = old_r // r
        old_r, r = r, old_r - q * r
        old_s, s = s, old_s - q * s
    return old_r, old_s, (old_r - old_s * a) // b if b else 0

gcdm = lambda *args: reduce(gcd, args, 0)
lcm = lambda a, b: a * b // gcd(a, b)
lcmm = lambda *args: reduce(lcm, args, 1)

########################## FACTORS #################################
def memodict(f):
    """memoization decorator for a function taking a single argument"""
    class memodict(dict):
        def __missing__(self, key):
            ret = self[key] = f(key)
            return ret

    return memodict().__getitem__

def pollard_rho(n):
    """returns a random factor of n"""
    if n & 1 == 0:
        return 2
    if n % 3 == 0:
        return 3

    s = ((n - 1) & (1 - n)).bit_length() - 1
    d = n >> s
    for a in [2, 325, 9375, 28178, 450775, 9780504, 1795265022]:
        p = pow(a, d, n)
        if p == 1 or p == n - 1 or a % n == 0:
            continue
        for _ in range(s):
            prev = p
            p = (p * p) % n
            if p == 1:
                return gcd(prev - 1, n)
            if p == n - 1:
                break
        else:
            for i in range(2, n):
                x, y = i, (i * i + 1) % n
                f = gcd(abs(x - y), n)
                while f == 1:
                    x, y = (x * x + 1) % n, (y * y + 1) % n
                    y = (y * y + 1) % n
                    f = gcd(abs(x - y), n)
                if f != n:
                    return f
    return n

@memodict
def prime_factors(n):
    """returns a Counter of the prime factorization of n"""
    if n <= 1:
        return Counter()
    f = pollard_rho(n)
    return Counter([n]) if f == n else prime_factors(f) + prime_factors(n // f)

def distinct_factors(n):
    """returns a list of all distinct factors of n"""
    factors = [1]
    for p, exp in prime_factors(n).items():
        factors += [p**i * factor for factor in factors for i in range(1, exp + 1)]
    return factors

def all_factors(n):
    """returns a sorted list of all distinct factors of n"""
    small, large = [], []
    for i in range(1, int(n**0.5) + 1, 2 if n & 1 else 1):
        if not n % i:
            small.append(i)
            large.append(n // i)
    if small[-1] == large[-1]:
        large.pop()
    large.reverse()
    small.extend(large)
    return small

############################## FFT #################################
MOD = 10**9 + 7
def fft(a, inv=False):
    n = len(a)
    w = [cmath.rect(1, (-2 if inv else 2) * cmath.pi * i / n) for i in range(n >> 1)]
    rev = [0] * n
    for i in range(n):
        rev[i] = rev[i >> 1] >> 1
        if i & 1:
            rev[i] |= n >> 1
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]

    step = 2
    while step <= n:
        half, diff = step >> 1, n // step
        for i in range(0, n, step):
            pw = 0
            for j in range(i, i + half):
                v = a[j + half] * w[pw]
                a[j + half] = a[j] - v
                a[j] += v
                pw += diff
        step <<= 1

    if inv:
        for i in range(n):
            a[i] /= n

def fft_conv(a, b):
    s = len(a) + len(b) - 1
    n = 1 << s.bit_length()
    a.extend([0.0] * (n - len(a)))
    b.extend([0.0] * (n - len(b)))

    _=fft(a), fft(b)
    del _
    for i in range(n):
        a[i] *= b[i]
    fft(a, True)

    a = [a[i].real for i in range(s)]
    return a

############################# PRIMES ################################
def prime_sieve(n):
    """returns a sieve of primes >= 5 and < n, Sieve of Eratosthenes"""
    flag = n % 6 == 2
    sieve = bytearray((n // 3 + flag >> 3) + 1)
    for i in range(1, int(n**0.5) // 3 + 1):
        if not (sieve[i >> 3] >> (i & 7)) & 1:
            k = (3 * i + 1) | 1
            for j in range(k * k // 3, n // 3 + flag, 2 * k):
                sieve[j >> 3] |= 1 << (j & 7)
            for j in range(k * (k - 2 * (i & 1) + 4) // 3, n // 3 + flag, 2 * k):
                sieve[j >> 3] |= 1 << (j & 7)
    return sieve

def prime_list(n):
    """returns a list of primes <= n"""
    res = []
    if n > 1:
        res.append(2)
    if n > 2:
        res.append(3)
    if n > 4:
        sieve = prime_sieve(n + 1)
        res.extend(3 * i + 1 | 1 for i in range(1, (n + 1) // 3 + (n % 6 == 1)) if not (sieve[i >> 3] >> (i & 7)) & 1)
    return res

def is_prime(n):
    """returns True if n is prime else False, MRP-Test"""
    if n < 5 or n & 1 == 0 or n % 3 == 0:
        return 2 <= n <= 3
    s = ((n - 1) & (1 - n)).bit_length() - 1
    d = n >> s
    for a in [2, 325, 9375, 28178, 450775, 9780504, 1795265022]:
        p = pow(a, d, n)
        if p == 1 or p == n - 1 or a % n == 0:
            continue
        for _ in range(s):
            p = (p * p) % n
            if p == n - 1:
                break
        else:
            return False
    return True

############################## CRT ##################################
def chinese_remainder(a, p):
    """returns x s.t. x = a[i] (mod p[i]) where p[i] is prime for all i"""
    prod = reduce(op.mul, p, 1)
    x = [prod // pi for pi in p]
    return sum(a[i] * pow(x[i], p[i] - 2, p[i]) * x[i] for i in range(len(a))) % prod

def composite_crt(b, m):
    """returns x s.t. x = b[i] (mod m[i]) for all i"""
    x, m_prod = 0, 1
    for bi, mi in zip(b, m):
        g, s, _ = extended_gcd(m_prod, mi)
        if ((bi - x) % mi) % g:
            return None
        x += m_prod * (s * ((bi - x) % mi) // g)
        m_prod = (m_prod * mi) // gcd(m_prod, mi)
    return x % m_prod

########################### PRIMITIVE ROOT ##########################
def ilog(n):
    """returns the smallest a, b s.t. a**b = n for integer a, b"""
    a = n.bit_length()
    for b in range(a, 0, -1):
        lo, hi = 1, 1 << (a // b + 1)
        while lo < hi:
            mi = (lo + hi) // 2
            a_b = mi**b
            if a_b == n:
                return mi, b
            if a_b > n:
                hi = mi
            else:
                lo = mi + 1

def primitive_root(p):
    """returns a primitive root of p"""
    factors = prime_factors(p - 1)

    for i in range(2, p + 1):
        ok = True
        for j in factors:
            ok &= pow(i, (p - 1) // j, p) != 1
        if ok:
            return i

    return None

############################# MISC ##################################
def phi(n):
    """returns phi(x) for all x <= n"""
    sieve = [i if i & 1 else i // 2 for i in range(n + 1)]
    for i in range(3, n + 1, 2):
        if sieve[i] == i:
            for j in range(i, n + 1, i):
                sieve[j] = (sieve[j] // i) * (i - 1)

    return sieve

def discrete_log(a, b, mod):
    """
    Returns smallest x > 0 s.t. pow(a, x, mod) == b or None if no such x exists.
    Note: works even if a and mod are not coprime.
    """
    n = int(mod**0.5) + 1

    # tiny_step[x] = maximum j <= n s.t. b * a^j % mod = x
    tiny_step, e = {}, 1
    for j in range(1, n + 1):
        e = e * a % mod
        if e == b:
            return j
        tiny_step[b * e % mod] = j

    # find (i, j) s.t. a^(n * i) % mod = b * a^j % mod
    factor = e
    for i in range(2, n + 2):
        e = e * factor % mod
        if e in tiny_step:
            j = tiny_step[e]
            return n * i - j if pow(a, n * i - j, mod) == b else None

def modinv(a, m):
    """returns the modular inverse of a w.r.t. to m, works when a and m are coprime"""
    g, x, _ = extended_gcd(a % m, m)
    return x % m if g == 1 else None

#----------------------------- REGION END -----------------------------#

#-------------------------------- DOCS --------------------------------#
''' 
gcd(x, y), gcdm(*args) : greatest common divisor of x and y 
lcm(x, y), lcmm(*args) : lcm of x and y 
extended_gcd(a, b): Returns gcd(a, b), s, r s.t. a * s + b * r == gcd(a, b) 

memodict(f): memoization decorator for a function taking a single argument 
pollard_rho(n): Returns a random factor of n 
prime_factors(n) @ memodict : Returns a Counter of the prime factorization of n 
distinct_factors(n): Returns a list of all distinct factors of n 
all_factors(n): Returns a sorted list of all distinct factors of n 

fft(a, inv = False), fft_conv(a, b) : FFT

prime_sieve(n): Returns a sieve of primes >= 5 and < n, Sieve of Eratosthenes 
prime_list(n): Returns a list of primes <= n 
is_prime(n): Returns True if n is prime else False, MRP-Test 

chinese_remainder(a, p): Returns x s.t. x = a[i] (mod p[i]) where p[i] is prime for all i 
composite_crt(b, m): Returns x s.t. x = b[i] (mod m[i]) for all i 

discrete_log(a, b, mod): Returns smallest x > 0 s.t. pow(a, x, mod) == b or None if no such x exists.

ilog(n): Returns the smallest a, b s.t. a**b = n for integer a, b 
primitive_root(p): Returns a primitive root of p 

phi(n): Returns euler's phi(x) for all x <= n 
modinv(a, m): Returns the modular inverse of a w.r.t. to m, works when a and m are coprime 

inp() : For taking integer inputs. 
invr() : For taking space seperated integer variable inputs 
invrs() : For taking space seperated string variable inputs 
inlt(): List of space seperated integer variable inputs 
inlts(): List of space seperated string variable inputs 
infn(fn) : map(fn, input().split())

print_rev(seq: iterable): prints the sequence in reverse
print_yn(value: bool, **kwargs): print(("NO", "YES")[bool], **kwargs)
'''
#----------------------------- DOCS END -------------------------------#


#---------------------------- DRIVER CODE -----------------------------#
if __name__ == "__main__": 
    for _ in range(inp()): solve()