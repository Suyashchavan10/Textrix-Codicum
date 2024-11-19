import sys

def pseudocode_to_cpp(pseudocode_file, output_file):
    # Read pseudocode from file
    with open(pseudocode_file, 'r') as file:
        pseudocode = file.read()

    # Convert pseudocode to C++ code (example logic)
    cpp_code = pseudocode.replace('print', 'std::cout <<').replace('end', ';\n')

    # Write C++ code to output file
    with open(output_file, 'w') as file:
        file.write(cpp_code)

if __name__ == "__main__":
    pseudocode_file = sys.argv[1]
    output_file = sys.argv[2]
    pseudocode_to_cpp(pseudocode_file, output_file)
