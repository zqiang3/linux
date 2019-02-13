#coding: utf-8
"""
多项式加法
"""


class Value(object):

    def __init__(self, coe=0, exp=0):
        self.coe = coe
        self.exp = exp

    def __str__(self):
        return '(%s, %s)' % (self.coe, self.exp)

    def __add__(self, other):
        assert(self.exp == other.exp)
        return Value(self.coe + other.coe, self.exp)


class Node(object):

    value = Value()
    next = None

    def __init__(self, value):
        self.value = value
    

class LinkList(object):

    def __init__(self):
        self.head = Node(Value())
        self.next = None


    def append(self, value):
        pre = self.head
        cur = pre.next
        while cur and (cur.value.exp < value.exp):
            pre = cur
            cur = cur.next

        if cur and cur.value.exp == value.exp:
            cur.value.coe += value.coe
        else:
            node = Node(value)
            pre.next = node
            node.next = cur

    def __add__(self, ano):
        cur = self.head.next
        acur = ano.head.next
        r = LinkList()
        while cur or acur:
            if not cur:
                r.append(acur.value)
                acur = acur.next
            elif not acur:
                r.append(cur.value)
                cur = cur.next
            else:
                if cur.value.exp < acur.value.exp:
                    r.append(cur.value)
                    cur = cur.next
                elif cur.value.exp > acur.value.exp:
                    r.append(acur.value)
                    acur = acur.next
                else:
                    r.append(cur.value + acur.value)
                    cur = cur.next
                    acur = acur.next

        return r

    def __str__(self):
        cur = self.head.next
        out = '['
        while cur:
            out += '%s, ' % cur.value
            cur = cur.next

        return out[:-2] + ']'


link = LinkList()
link.append(Value(1, 12))
link.append(Value(2, 7))
link.append(Value(3, 2))
link.append(Value(3, 9))
link.append(Value(3, 5))

ano = LinkList()
ano.append(Value(1, 13))
ano.append(Value(1, 3))
ano.append(Value(1, 7))
ano.append(Value(1, 2))
ano.append(Value(1, 9))
print link
print ano
print link + ano

        


