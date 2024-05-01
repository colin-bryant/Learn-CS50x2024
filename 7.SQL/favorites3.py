import csv
# 如果自己创建一个字典可能有点痛苦

from collections import Counter

with open("favorites.csv","r") as file:

    reader = csv.DictReader(file)
    # Counter 将一切初始化为零
    counts = Counter()

    for row in reader:
        favorite = row["problem"]
        counts[favorite] += 1
favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
