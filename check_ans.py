import filecmp
import os

dir_path = "./testcases/"
output_dir_path = "./testcases/result/"

if (not os.path.exists(output_dir_path)):
    os.mkdir(output_dir_path)

for i in range(len([entry for entry in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, entry))]) - 1):
    print("Test Case " + str(i + 1))
    print(filecmp.cmp(os.path.join(output_dir_path, "ans" + str(i + 1) + ".c1"), os.path.join(output_dir_path, "test" + str(i + 1) + ".c1")))
    print('\n')
    