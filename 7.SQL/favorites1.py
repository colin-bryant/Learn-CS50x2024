import csv

with open("favorites.csv","r") as file:

    reader = csv.DictReader(file)
    # count =dict()
    counts = {}
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite]+=1
        else:
            # 在 Python 中，如果尝试给一个不存在的键赋值，会抛出 KeyError 异常
            counts[favorite] = 1

# Print counts
for favorite in sorted(counts,key=counts.get,reverse=True):
    print(f"{favorite}: {counts[favorite]}")
