from cs50 import get_int

def main():
    i = 1
    product_sum = _sum = 0
    
    while True:
        number = num2 = get_int("Number: ")
        if number > 0:
            break
        
    while number > 0:
        if (i % 2) == 0:
            product = (number % 10) * 2
            
            if product > 9:
                product_sum += int(product % 10)
                product /= 10
                product_sum += int(product % 10)
            else:    
                product_sum += int(product)
        else:
            _sum += number % 10
        
        number /= 10
        number = int(number)
        i += 1
        
    i -= 1
    two_digits = first_two_digits(num2, i)

    if ((_sum + product_sum) % 10) != 0 or i < 13:
        print("INVALID")
    else  :  
        if i == 15 and (two_digits == 34 or two_digits == 37):
            print("AMEX")
        elif i == 13:
            print("VISA")
        else:
            if two_digits < 56 and two_digits > 50:
                print("MASTERCARD")
            elif two_digits >= 40 and two_digits < 50:
                print("VISA")
            else:
                print("INVALID")
    exit(0)
    
def first_two_digits(a, i):
    for j in range (1, i-1):
        a /= 10
    return int(a)    

main()    