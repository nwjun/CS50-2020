from sys import argv, exit
import csv

if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

#open file
datafile = open(argv[1], "r")
checkfile = open(argv[2], "r")

#read database into dict
database = csv.DictReader(datafile)
dna_sequence = checkfile.readline()
#store keys 
keys = database.fieldnames

#1st key is name
maxi = len(keys) - 1
length = len(dna_sequence)

#declare list with number of keys
occurence = [0] * maxi

#counting largest consequtive STR sequences and store in list
for i in range(maxi):
    temp = 0
    r = len(keys[i + 1])
    j = 0
    while j < (length - r + 1):
        if dna_sequence[j: j+r ] == keys[i + 1]:
            temp += 1
            j += r 
            
        else:
            if temp > occurence[i]:
                occurence[i] = temp
            j += 1
            temp = 0    

#searching in dictionaries and show name if found  
for row in database:
    found = True
    for i in range(maxi):
        if (int(row[keys[i + 1]]) == occurence [i]) and i == (maxi - 1) and found == True:
            print(row["name"])
            datafile.close()
            checkfile.close()
            exit(0)
        elif int(row[keys[i + 1]]) != occurence [i]:
            #if different from database toggle to false
            found = False
            
print("No match")

#close file
datafile.close()
checkfile.close()

exit(1)