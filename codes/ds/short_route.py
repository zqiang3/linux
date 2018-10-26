import math

MAX = 20000


def get_min(dots, left, right):
    if(left == -1 or right == -1):
        return MAX

    if(left >= right):
        return MAX

    if(right - left == 1):
        return get_distance(dots[left], dots[right])

    left_max, right_min, middle = split_dots(dots, left, right)
    left_min = get_min(dots, left, left_max)
    right_min = get_min(dots, right_min, right)
    delta = min(left_min, right_min)

    merge_min = get_merge_min(dots, left, left_max, middle, delta, right_min, right)
    return min(left_min, right_min, merge_min)


def get_merge_min(dots,left, left_max, middle, delta, right_min, right):
    p_x = []
    for i in xrange(left_max, left-1, -1):
        if middle - dots[i][0] <= delta:
            p_x.append(i)
        else:
            break

    min = MAX
    for x in p_x:
        dis = get_merge_xy_min(dots, x, middle, right_min, right)
        if dis < min:
            min = dis

    return min


def get_merge_xy_min(dots, left_p, middle, right_min, right):
    right_p = []
    for i in xrange(right_min, right+1):
        if dots[i][0] - middle <= delta:
            if abs(dots[i][1] - dots[left_p][1]) <= delta:
                p_x.append(i)
        else:
            break

    min = MAX 
    for i in right_p:
        dis = get_distance(dots, left_p, i)
        if dis < min:
            min = dis

    return min


def get_distance(d1, d2):
    x1, y1 = d1
    x2, y2 = d2
    return math.sqrt((x2-x1)**2 + (y2-y1)**2)


def split_dots(dots, left, right):
    middle = get_middle(dots)
    left_max = dots[0][0]
    right_min = dots[-1][0]

    left_max = -1
    right_min = -1

    for i in xrange(left, right+1):
        if dots[i][0] <= middle:
            left_max = i 
        else:
            right_min = i
            break

    return left_max, right_min, middle


def get_middle(dots):
    sum_x = 0
    for dot in dots:
        sum_x += dot[0]
    return sum_x * 1.0 / len(dots)




dots = [(1, 7), (3, 4), (2, 6)]
sorted_dots = sorted(dots, key=lambda x: x[0])
min_dis = get_min(sorted_dots, 0, 2)
print "min distance: %s" % min_dis
