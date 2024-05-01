# people = [
#   {
#     "name":"Carter",
#     "number":"12313"
#   },
#   {
#     "name":"David",
#     "number":"1232213"
#   },
#   {
#     "name":"John",
#     "number":"145242313"
#   },
# ]

# name = input("Name: ")

# for person in people:
#   if person["name"]== name:

#     print(f"Found {person['number']}")
#     break
# else:
#   print("Not found")



people = {
  "Carter":"12313",
  "David":"1232213",
  "John":"123ww13",
}
name = input("Name: ")

if name in people:
  number = people[name]
  print(f"Found {number} ")
else:
  print("Not found")
