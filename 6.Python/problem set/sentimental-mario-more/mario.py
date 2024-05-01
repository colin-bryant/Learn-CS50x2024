
def get_int(prompt):
    while True:
        try:
            num = int(input(prompt))
            if num >= 1 and num <=8:
                return num
            else:
                print("Please enter a positive integer between 1 and 8")
        except ValueError:
            print("Please enter a valid integer")
def main():
    height = get_int("Enter the height of the half-pyramin(1-8): ")

    # Generate half-pyramin
    # range() 函数生成的序列是开区间，不包括结束值。
    for i in range(1,height+1):
        # print space
        print(" " * (height-i),end="")

        # print hashes
        print("#" * i + "  " + "#" * i)



# 只有在该脚本被直接执行时才会被执行，而当该脚本被作为模块导入到其他脚本中时，这部分代码不会被执行。
if __name__ == "__main__":
    main()
