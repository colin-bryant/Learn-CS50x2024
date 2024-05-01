import csv

# file=open("favorites.csv","r")
# # Do something with file
# close(file)

with open("favorites.csv","r") as file:
    # reader = csv.reader(file)
    # ['Timestamp', 'language', 'problem'],['10/30/2023 13:38:01', 'Python', 'Hello, World'],
    reader = csv.DictReader(file) # {'Timestamp': '10/30/2023 13:38:01', 'language': 'Python', 'problem': 'Hello, World'},
    # Skip header row
    # next(reader)
    # Iterate over CSV file, printing each favorite
    scratch, c, python = 0, 0, 0
    for row in reader:
        # favorite = row[1] 如果列被移动或者被交换了怎么办 python允许你用列表的键来建立索引 csv.DistReader
        # favorite = row["language"]
        # print(favorite)
           # Counts


    # Iterate over CSV file, counting favorites

        favorite = row["language"]
        if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1

# Print counts
print(f"Scratch: {scratch}")
print(f"C: {c}")
print(f"Python: {python}")




