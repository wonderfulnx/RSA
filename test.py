import os
import time

def get_file_modify(file_path):
    ts = os.path.getmtime(file_path)
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(ts))
    
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
    ans = line2.split()
    a = int(num[0], 16)
    b = int(num[1], 16)
    ans1 = int(ans[0], 16)
    ans2 = int(ans[1], 16)
    if a // b != ans1 or a % b != ans2:
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