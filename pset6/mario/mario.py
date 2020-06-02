from cs50 import get_int

def main():
    level = 1
    height = get_positive_int()
    
    while True: 
       for i in range(height - level):
           print(" ", end = "")
       print_hashes(level)   
       print("  ", end = "")
       print_hashes(level)
       print()
       level += 1
       if level > height:
           break

def get_positive_int():
    while True:
        n = get_int("Height (1-8): ")
        if n > 0 and n < 9:
            break
    return n

def print_hashes(level):
    i = 0
    for i in range(level):
        print("#", end = "")
        
main()        