
def main():

    text=str(input("Text: "))


    # index = 0.0588 * L - 0.296 * S - 15.8
    # 单词数
    # words = text.count(' ') + 1
    letters = 0
    words = 1
    sentences = 0
    for char in text:
        if char.isalpha():
            letters += 1
        elif char.isspace():
            words += 1
        elif char in ['.','?','!']:
            sentences += 1
    L = (letters/words)*100
    S = (sentences/words)*100

    index =round(0.0588*L-0.296*S-15.8)

    if int(index) < 1:
        print("Before Grade 1")
    elif int(index) > 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(index)}")







if __name__ == "__main__":
    main()
