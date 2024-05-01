import csv
# 如果自己创建一个字典可能有点痛苦

from collections import Counter

with open("favorites.csv","r") as file:

    reader = csv.DictReader(file)
    # Counter 将一切初始化为零
    counts = Counter()

    for row in reader:
        favorite = row["language"]
        counts[favorite] += 1

# Print counts
# for favorite in sorted(counts,key=counts.get,reverse=True):
#     print(f"{favorite}: {counts[favorite]}")
# most_common() 方法返回一个按出现次数降序排列的元素和计数值的列表。
for favorite,count in counts.most_common():
    print(f"{favorite}:{count}")
