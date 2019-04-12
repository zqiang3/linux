## defaultdict

defaultdict([default_factory], ...)

此类型与字典基本一样，不同之处在于对**键不存在**时的处理上，使用提供的工厂函数提供默认值。

```
from collections import defaultdict

#d = defaultdict(list)
d = defaultdict(int)

d['name'] += 1

print d
```

