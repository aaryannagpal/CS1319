import os

if __name__ == "__main__":
    expected_dir = "./sample_output_A3/"
    expected_outs = [f for f in os.listdir(expected_dir) if f.endswith(".output")]

    actual_dir = "./output/"
    actual_outs = [f for f in os.listdir(actual_dir) if f.endswith(".output")]

    # check if all expected outputs and actual outputs are same
    if(actual_outs != expected_outs):
        print("Files List Not Same")
        print("Expected Files: ", expected_outs)
        print("Actual Files: ", actual_outs)
        exit()
    else:
        print("All Files Present\n\n")

    for expected_file in expected_outs:
        temp = expected_file
        expected_file_path = expected_dir + expected_file
        actual_file_path = actual_dir + expected_file

        # open expected file
        expected_file = open(expected_file_path, "r")
        expected_lines = expected_file.readlines()

        # open actual file
        actual_file = open(actual_file_path, "r")
        actual_lines = actual_file.readlines()

        print(f"Checking {temp}...")

        # check if contents are the same
        if(expected_lines == actual_lines):
            print(f"File {expected_file_path} is same as {actual_file_path}\n")
            
        else:
            print(f"Not Same: {temp}")
            print("Diff Output:")
            os.system(f"diff {expected_file_path} {actual_file_path}")
            print("")