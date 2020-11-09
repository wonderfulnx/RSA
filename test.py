import os
import time
import random

###################################################################################
####################           Util functions           ###########################
###################################################################################
def get_file_modify(file_path):
    ts = os.path.getmtime(file_path)
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(ts))

def binpow(b, e, m):
    result = 1
    while e != 0:
        if (e&1) == 1:
            # ei = 1, then mul
            result = (result * b) % m
        e >>= 1
        # b, b^2, b^4, b^8, ... , b^(2^n)
        b = (b*b) % m
    return result
    
def is_prime(n, trials = 10):
    assert n >= 2
    # 2是素数~
    if n == 2:
        return True
    # 先判断n是否为偶数，用n&1==0的话效率更高
    if n % 2 == 0:
        return False
    # 把n-1写成(2^s)*d的形式
    s = 0
    d = n - 1
    while True:
        quotient, remainder = divmod(d, 2)
        if remainder == 1:
            break
        s += 1
        d = quotient
    assert(2 ** s * d == n - 1)
 
    # 测试以a为底时，n是否为合数
    def try_composite(a):
        if pow(a, d, n) == 1: # 相当于(a^d)%n
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1: #相当于(a^((2^i)*d))%n
                return False
        return True # 以上条件都不满足时，n一定是合数
    
    # trials为测试次数，默认测试5次
    # 每次的底a是不一样的，只要有一次未通过测试，则判定为合数
    for i in range(trials):
        a = random.randrange(2, n)
        if try_composite(a):
            return False

    return True #通过所有测试，n很大可能为素数

###################################################################################
####################                 Tests              ###########################
###################################################################################
def test_plus(line1, line2):
    num = line1.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    ans = int(line2, 16)
    if a + b != ans:
        return False
    return True

def test_sub(line1, line2):
    num = line1.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    ans = int(line2, 16)
    if a - b != ans:
        return False
    return True

def test_mul(line1, line2):
    num = line1.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    ans = int(line2, 16)
    if a * b != ans:
        return False
    return True

def test_div(line1, line2):
    num = line1.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    ans = int(line2, 16)
    if a % b != ans:
        return False
    return True

def test_binpow(line1, line2):
    num = line1.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    m = int(num[2], 16)
    ans = int(line2, 16)
    if binpow(a, b, m) != ans:
        return False
    return True

def test_prime(line1, line2):
    if (line1):
        a = int(line1, 16)
        if not is_prime(a):
            return False
    if (line2):
        b = int(line2, 16)
        if not is_prime(b):
            return False
    return True

if __name__ == "__main__":
    file_path = 'cmake-build-release/data.txt'
    f = open(file_path)
    print(f"INFO - data File is modified at {get_file_modify(file_path)}")
    line1 = f.readline()
    line2 = f.readline()
    error_num = 0
    while line1 and line2:
        if (test_div(line1, line2) == False):
            error_num += 1
        line1 = f.readline()
        line2 = f.readline()
    
    if error_num == 0:
        print('No Error Found!')
    else:
        print(f'Found {error_num} Errors!')

    f.close()