
while True:
    try:
        money = float(input("Change: "))
    except ValueError:
        # 跳过下面的语句继续循环
        print("Invalid Value")
        continue
    if money > 0:
        break
money =int(money * 100)


QUARTER = 25
DIME = 10
NICKEL = 5
PENNY = 1

count = 0

# count = count + money // QUARTER
count += money // QUARTER
money = money % QUARTER

count += money // DIME
money = money % DIME

count += money // NICKEL
money = money % NICKEL

count += money // PENNY

print(count)

