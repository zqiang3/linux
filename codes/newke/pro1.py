# -*- coding:utf-8 -*-
class Solution:
    # array 二维列表
    def Find(self, target, array):
        if not isinstance(array, list):
            return False

        if not isinstance(array[0], list):
            return False

        rows = len(array)
        cols = len(array[0])
        row, col = 0, cols-1

        while True:            
            if row >= rows or col < 0:
                break

            value = array[row][col]
            if value == target:
                return True
            elif value > target:
                col -= 1
            else:
                row += 1

        return False