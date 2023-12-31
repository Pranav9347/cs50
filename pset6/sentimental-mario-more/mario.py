# TODO
import cs50


def generate_half_pyramid(h):
    for i in range(h):  # outer loop to print out each line(0th level)
        for j in range(h - 1 - i):  # 1st lvl inner loop-1 to print spaces
            print(" ", end="")
        for k in range(i + 1):  # 1st lvl inner loop-2 to print 1st half
            print("#", end="")
        print("  ", end="")  # gap betwwen the two half-pyramids
        for k in range(i + 1):  # 1st lvl inner loop-3 to print 2nd half
            print("#", end="")
        print("\n", end="")


height = -1
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

generate_half_pyramid(height)
