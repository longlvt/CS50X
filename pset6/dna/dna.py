# Simulate a sports tournament

import csv
import sys
import os


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    elif (os.path.isfile(sys.argv[1]) == False or os.path.isfile(sys.argv[2]) == False):
        print("Invalid path")
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database
    data = []
    headers = []
    with open(sys.argv[1], "r") as header_file:
        reader = csv.reader(header_file)
        headers = next(reader, None)
    # print(f"HEADERS FOUND: {headers}")

    with open(sys.argv[1], "r") as data_file:
        reader = csv.DictReader(data_file)
        for row in reader:
            for key in headers:
                if key != 'name':
                    row[key] = int(row[key])
            data.append(row)

    # List of sample need to matched
    samples = headers[1:]
    # print(f"SAMPLES FOUND: {samples}")

    # Read sequence and find the sample
    text_file = open(sys.argv[2], "r")
    sequence = text_file.read()

    dict_STR = find_matched(samples, sequence)
    # cons_count = cons_check(sample_found, sequence)
    # dict_STR[sample_found] = cons_count

    # Find the name if matched
    name = find_name(dict_STR, data)

    # Show result
    if name != '':
        print(name)
    else:
        print("No match")

# Function to check any matched sample from the sequence.


def find_matched(samples, sequence):
    sample_dict = {}
    for sample in samples:
        # print("++++++++++++++++++++++++")
        matched_position = []
        max_cons = 0
        count_consecutive = 1
        length = len(sample)

        # Find the position in sequence that from which, successive sub-string matched the sample
        for id in range(0, len(sequence) - length):
            # print(f"CHECK: {sequence[id:id + length]} with {sample}", end='')
            if sequence[id:id + length] == sample:
                # print("---> HITSS")
                matched_position.append(id)
            # print()
        # print(f"POSITION FOUND: {matched_position}")

        # Find the maximum consecutive repeat of sample in sequence, then add to a dictionary
        if len(matched_position) > 0:
            max_cons = 1
            consecutive = 1
            for idx in range(len(matched_position) - 1):
                if matched_position[idx + 1] - matched_position[idx] == length:
                    consecutive += 1
                else:
                    consecutive = 1
                if consecutive > max_cons:
                    max_cons = consecutive

        # Add data to a dictionary
        sample_dict[sample] = max_cons
        # print(f"HERE: {sample_dict}")

    return sample_dict

# Find the name from database that matched with values in sample


def find_name(myDict, data):
    myDictKeys = list(myDict.keys())
    # Go through each element in the dictionary data
    for each in data:
        eachKeys = list(each.keys())

        # Only check if the element in the dictionary data has the same number of STR with the dictionary found from sequence.
        if len(myDictKeys) == len(eachKeys) - 1:
            # Start counter with the number of keys in STR found from the sequence.
            count = len(myDictKeys)

            # Get the key from an element in data
            for key in each:
                # Only continue to check value if the key exists in the list of STR found from the sequence.
                if key in myDictKeys:
                    # If there's one mis-matched field, proceed to check the next element in the dictionary data
                    if each[key] != myDict[key]:
                        break
                    else:  # If there's one matched field, reduce the counter by 1
                        count -= 1
            if count == 0:  # If counter reach 0 after checking all key in the elemenent of the dictionary data, means all matched.
                return each['name']
    return ''


if __name__ == "__main__":
    main()
