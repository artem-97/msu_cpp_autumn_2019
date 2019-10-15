import os

progName = "calc"
correctTests = [
        ('12-2', '10'),
        ('-2 +2','0'),
        ('19+ 232','251'),
        ('--- 2     + ++++17', '15'),
        ('----2----15', '17'),
        ('(12-2) * (12--3)', '150'),
        ('(((-   45)))', '-45'),
        ]

incorrectTests = [
        ('-', 'Syntax error\n'),
        ('))', 'Syntax error\n'),
        ('asd + 2', 'Invalid char\nSyntax error\n'),
        ]

def check(expr):
    return os.popen("echo " + '"' + expr + '"' + "|" + "./" + progName).read()
    

def test(inp):
    passed = 0
    for test in inp:
        if check(test[0]) != test[1]:
            print("Test not passed . Ans: ", check(test[0]), "Expected: ", test[1])
            print("-------")
        else:
            print(test[0], " = ", check(test[0]))
            print("Passed")
            passed += 1
    print("Passed ", passed / len(inp) * 100, "%" )


print("Correct input")
test(correctTests)

print('\n\n')

print("Incorrect input")
test(incorrectTests)

