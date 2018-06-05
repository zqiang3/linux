## 功能

insert()函数用于将指定对象插入列表的指定位置。

## 语法

list.insert(index, obj)

## 参数

index: 对象obj需要插入的索引位置。

obj: 插入列表中的对象。

## 场景

场景1：index=0时，从头部插入obj

场景2：index > 0 且 index < len(list)时，在index的位置插入obj

场景3：当index < 0 且 abs(index) < len(list)时，从中间插入obj，如: -1 表示从倒数第1位插入obj; -2 表示从倒数第1位插入obj

场景4：当index < 0 且 abs(index) >= len(list)时，从头部插入obj

场景5：当index >= len(list)时,从尾部插入obj

## 返回值

该方法没有返回值，但会在列表指定位置插入对象。