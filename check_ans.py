import filecmp
import os

reference_dir_path = "./reference/"
output_dir_path = "./output/"

for i in range(len([entry for entry in os.listdir(output_dir_path) if os.path.isfile(os.path.join(output_dir_path, entry))])):
    print("Test Case " + str(i + 1))
    print(filecmp.cmp(os.path.join(output_dir_path, "ans" + str(i + 1) + ".c1"), os.path.join(reference_dir_path, "test" + str(i + 1) + ".c1")))
    