from cs50 import get_string

s = get_string("Text: ")

letters = 0
words = 0
sentences = 0

word_len = 0
for c in s:
    # ".", "!" or "?" indicates the end of a word and a sentence
    if word_len != 0 and c in [".", "!", "?"]:
        sentences += 1
        word_len = 0
    
    # The beginning of a word
    elif word_len == 0 and c.isalpha() == True:
        letters += 1
        words += 1
        word_len += 1
    
    # The rest of a word
    elif word_len != 0 and c.isalpha() == True:
        letters += 1
        word_len += 1
    
    # The end of a word
    elif word_len != 0 and c == " ":
        word_len = 0

grade = round(0.0588 * (letters / words) * 100 - 0.296 * (sentences / words) * 100 - 15.8)

if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
