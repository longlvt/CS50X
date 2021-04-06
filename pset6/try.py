import csv
import sys
import os

data = []
headers = []

# Find the name from database that matched with values in sample
def find_name(myDict, data):
    myDictKeys = list(myDict.keys())
    for each in data:
        eachKeys = list(each.keys())
        if len(myDictKeys) == len(eachKeys) - 1: # Compare if the elements in data has the same number of STR with the dictionary from sequence.
            count = len(myDictKeys)
            for key in each:
                print(f"CHECKING FOR: {key}: {each[key]}")
                if key in myDictKeys:
                    print("check value")
                    if each[key] != myDict[key]:
                        break
                    else:
                        print("-->HITS")
                        count -= 1
                print()
            if count == 0:
                return each['name']
    return ''

# Function to check any matched sample from the sequence.
def find_matched(samples, sequence):
    matched = []
    for i in range(len(sequence) - 1):
        for j in range(i + 1, len(sequence)):
            if sequence[i:j] in samples:
                matched.append(sequence[i:j])
                print(f"FOUND: {matched}")
                break
    return matched

with open("dna/databases/small.csv", "r") as header_file:
    reader = csv.reader(header_file)
    headers = next(reader, None)

with open("dna/databases/small.csv", "r") as data_file:
    reader = csv.DictReader(data_file)
    for row in reader:
        for key in headers:
            if key != 'name':
                row[key] = int(row[key])
        data.append(row)

print(f"HEADERS: {headers}")
print(f"DATA: {data}")

# List of sample need to matched
samples = headers[1:]

 # Construct a dictionary to store STRs found from sequence
dict_STR = {}

# Read sequence and find the sample
sequence = open(sys.argv[2], "r")

sample_found = find_matched(samples, sequence)
print(sample_found)
# cons_count = cons_check(sample_found, sequence)
# dict_STR[sample_found] = cons_count

dict_STR = {'AGATC': 4, 'AATG': 1}
# Find the name if matched
name = find_name(dict_STR, data)

# Show result
if name != '':
    print(name)
else:
    print("No match")