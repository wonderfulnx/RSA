import os

if __name__ == "__main__":
    f = open('cmake-build-debug/data/data.txt')
    line1 = f.readline()
    line2 = f.readline()
    error_num = 0
    while line1 and line2:
        num = line1.split()
        ans = line2.split()
        a = int(num[0], 16)
        b = int(num[1], 16)
        ans1 = int(ans[0], 16)
        ans2 = int(ans[1], 16)
        if a // b != ans1 or a % b != ans2:
            error_num += 1
        line1 = f.readline()
        line2 = f.readline()
    
    if error_num == 0:
        print('No Error Found!')
    else:
        print(f'Found {error_num} Errors!')

    f.close()