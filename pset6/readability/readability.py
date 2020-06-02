from cs50 import get_string

text = get_string("Text:")
words = 1
index = sentence = letters = 0 
for i in range(len(text)):
    if text[i] in ["!", ".", "?"]:
        sentence += 1
    elif (text[i].isalpha()) == True:
        letters += 1
    elif text[i] == " ":
        words +=1
    else:
        pass

index = round(0.0588 * (letters / words * 100) - 0.296 * (sentence / words * 100) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

exit(0)    