

money = [1, 2, 5, 10, 20, 50, 100]
nums = [3, 1, 2, 1, 1, 3, 5]

sum = 442

money.reverse()
nums.reverse()


result = dict()
for i, m in enumerate(money):
    num = sum / m
    if num > nums[i]:
        num = nums[i]
    result[m] = num
    sum -= num * m


if sum == 0:
    print 'success'
    print result
else:
    print 'failed'
    print result
