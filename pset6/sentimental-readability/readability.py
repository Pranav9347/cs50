# TODO
import cs50


def determine_grade(text):
    letters, words, sentences = 0, 0, 0
    for c in text:
        if c.isalpha():
            letters += 1
        elif c == " ":
            words += 1
        elif c in [".", "!", "?"]:
            sentences += 1
    words += 1
    print(f"letters={letters}\nwords={words}\nsentences={sentences}")
    L = (letters / words) * 100
    S = (sentences / words) * 100
    return round(0.0588 * L - 0.296 * S - 15.8)




    # MAIN FUNCTION:

text = cs50.get_string("Text: ")
grade = determine_grade(text)
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
