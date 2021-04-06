from cs50 import get_int
height = ''
# print(type(height))
# while (height < 1 or height > 8):
#     height = get_int("Height: ")
while (height.strip().isdigit() == False or (height.strip().isdigit() == True and (int(height) < 1 or int(height) > 8))):
    height = input("Height: ")

for i in range(1, int(height) + 1):
    print(" " * (int(height) - i), end="")
    print("#" * i, end="")
    print(" " * 2, end="")
    print("#" * i)