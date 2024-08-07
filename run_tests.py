import os
import subprocess

# Define paths
inputs_folder = "inputs"
expected_outputs_folder = "outputs"
executable = "./catan"  

# List all input files
input_files = sorted([f for f in os.listdir(inputs_folder) if f.endswith('.txt')])

# Run the executable for each input file
for input_file in input_files:
    input_path = os.path.join(inputs_folder, input_file)
    expected_output_file = input_file.replace("input", "output")
    expected_output_path = os.path.join(expected_outputs_folder, expected_output_file)

    # Read input file content
    with open(input_path, 'r') as file:
        input_content = file.read()

    # Run the executable with the input file content
    try:
        result = subprocess.run([executable], input=input_content, capture_output=True, text=True)
        
        # Check if the program crashed
        if result.returncode != 0:
            print(f"Program crashed with input file {input_file}")
            continue

        # Compare the actual output with the expected output
        with open(expected_output_path, 'r') as expected_output:
            expected_content = expected_output.read()
            if result.stdout.strip() == expected_content.strip():
                print(f"Test passed for {input_file}")
            else:
                print(f"Output mismatch for {input_file}")
                

    except Exception as e:
        print(f"Error occurred while testing with {input_file}: {e}")

