import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/<database_file>.csv sequences/<given_sequence_file>.txt")

    # TODO: Read database file into a variable
    # creating a list of STR's:
    str = []
    # creating a list of suspects:
    sus = []
    # creating a list of dictionaries:
    database = []
    with open(f"{sys.argv[1]}") as file:
        csv_reader = csv.DictReader(file)
        file_reader = csv.reader(file)
        str = next(file_reader)
        file.seek(0)
        str.remove("name")
        for row in csv_reader:
            sus.append(row["name"])
            d = {}
            for i in range(len(str)):
                d[str[i]] = int(row[str[i]])
            database.append(d)

    # TODO: Read DNA sequence file into a variable
    with open(f"{sys.argv[2]}") as file:
        test_sample = file.readline()

    # TODO: Find longest match of each STR in DNA sequence
    sample = {}
    for i in range(len(str)):
        sample[str[i]] = longest_match(test_sample, str[i])

    # TODO: Check database for matching profiles
    for i in range(len(sus)):
        if sequence_matched(database[i], sample, str):
            print(sus[i])
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


def sequence_matched(person_data, sample, str):  # both args are dictionaries
    for i in range(len(str)):
        if person_data[str[i]] != sample[str[i]]:
            return 0
    return 1


main()
