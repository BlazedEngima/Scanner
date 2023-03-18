import filecmp
import os

test_file = "./testcases/result/test"
ans_file = "./testcases/result/ans"

for i in range(0, 5):
    print("Test Case " + str(i + 1))
    print(filecmp.cmp(test_file + str(i + 1) + ".c1", ans_file + str(i + 1) + ".c1"))
    print('\n')
    