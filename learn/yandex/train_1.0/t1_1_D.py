

a = int(input())
b = int(input())
c = int(input())
if c < 0 or a == 0 and b ** 2 != c:
    print('NO SOLUTION')
elif a == 0 and b ** 2 == c:
    print('MANY SOLUTIONS')
else:
    res = (c * c - b) / a
    if res % 1 == 0:
        print(int(res))
    else:
        print('NO SOLUTION')
