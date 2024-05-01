# s=input("Do you agree? ")

# if s=="Y" or s=="y":
#   print("Agreed")
# else:
#   print("Not agreed")

s=input("Do you agree? ").lower()

if s in ["y", "yes"]:
  print("Argeed")
elif s in ["n","no"]:
  print("Not argeed")

