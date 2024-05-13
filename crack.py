# 包含 '0123456789' 的 digits 字符串。
from string import digits
# 计算输入迭代的笛卡尔积
from itertools import product

for passcode in product(digits,repeat=4 ):
    print(passcode)