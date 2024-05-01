import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        exit(1)
    database = sys.argv[1]
    sample = sys.argv[2]
    # TODO: Read database file into a variable
    rows = []
    with open(database) as f:
        reader = csv.DictReader(f)
        try:
            for row in reader:
                # Convert values other than 'name' to integers
                # name,AGATC,AATG,TATC
                # Alice,2,8,3
                # Bob,4,1,5
                # Charlie,3,2,5
                for key,value in row.items():
                    if key != "name":
                        row[key]=int(value)
                rows.append(row)
        except csv.Error as e:
            sys.exit('file {}, line {}: {}'.format(database, reader.line_num, e))
    # keys 变量将包含除了 'name' 列以外的所有列名。
    # keys = []
    # for key in rows[0].keys():
    # if key != 'name':
    #     keys.append(key)
    keys = [key for key in rows[0].keys() if key != 'name']
    # TODO: Read DNA sequence file into a variable
    s = ''
    with open(sample) as f:
        s = f.read()
    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for key in keys:
        matches[key]=longest_match(s,key)
    # TODO: Check database for matching profiles
    for row in rows:
        # matched = True
            # for key in keys:
            #     if row[key] != matches[key]:
            #         matched = False
            #          break

            # if matched:
            # 执行某些操作

        if all(row[key] == matches[key] for key in keys):
            print(row['name'])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # name,AGATC,AATG,TATC
            # Alice,2,8,3
            #AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
