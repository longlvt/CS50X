from cs50 import get_string

string = get_string("Text: ")

# Constructe list of ASCII code for charater
charList = []
for i in range(65, 91, 1):
    charList.append(i)
    charList.append(i + 32)
# print(charList, len(charList))

letterCount = 0
wordCount = 0
if (len(string) > 0):
    wordCount = 1
sentenceCount = 0
for char in string:
    asciiCode = ord(char)
    # print(char, asciiCode)
    if (asciiCode in charList):
        letterCount += 1
        # print("LETTER DETECTED: ", letterCount)
    elif (asciiCode == 32):
        wordCount += 1
        # print("WORD DETECTED: ", char, asciiCode, wordCount)
    elif (asciiCode in [33, 46, 63]):
        sentenceCount += 1
        # print("SENTENCE DETECTED: ", sentenceCount)

print(letterCount, wordCount, sentenceCount)
L = 100 * letterCount / wordCount
S = 100 * sentenceCount / wordCount
X = round(0.0588 * L - 0.296 * S - 15.8)

if (X >= 16):
    print("Grade 16+")
elif (X < 1):
    print("Before Grade 1")
else:
    print(f"Grade {X}")