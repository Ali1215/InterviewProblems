def takeInput():
    n = int(input())  # input how many applicants

    applicants = []
    for _ in range(n):
        applicants.append(int(input()))  # input wealth of each applicant
    applicants.sort()  # sort applicants in ascending order
    return n, applicants


def mainLoop(n, l):

    j = 1  # millions of dollars minimum
    i = 0  # index in list
    while i < n:
        if applicants[i] >= j:  # check if minimum has been exceeded
            # break if minimum dollars exceed number of applicants
            if j > (n - i):
                break
            # otherwise increment the limit
            j += 1
        else:
            # dollar minimum not exceeded so increment index
            i += 1
    return j-1  # subtract one since dollar limit exceeded number of applicants


if __name__ == "__main__":
    n, applicants = takeInput()
    j = mainLoop(n, applicants)
    print(j)