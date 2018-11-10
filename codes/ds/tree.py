
class Node(object):

    def __init__(self, data, lchild=None, rchild=None):
        self.data = data
        self.lchild = lchild
        self.rchild = rchild

    def __str__(self):
        return 'data={}, lchild={}, rchild={}'.format(self.data, id(self.lchild), id(self.rchild))


class Tree(object):

    def __init__(self):
        self.root = None

    def set_root(self, node):
        self.root = node

    def insert(self, data):
        node = Node(data)
        if not self.root:
            self.root = node
            return

        p = self.root
        cur = self.root
        while cur:
            p = cur
            if data < cur.data:
                cur = cur.lchild
            else:
                cur = cur.rchild

        if data < p.data:
            p.lchild = node
        else:
            p.rchild = node

    def traverse(self):

        def _traverse(root):
            if root is None:
                return

            _traverse(root.lchild)
            print root.data
            _traverse(root.rchild)

        _traverse(self.root)





tree = Tree()
tree.insert(1)
tree.insert(9)
tree.insert(3)
tree.insert(2)
tree.insert(7)
tree.insert(5)

tree.traverse()

