import os

def find_directories_with_largest_files(min_lines=100):
    printed_dirs = set()

    for root, _, files in os.walk("."):
        for file in files:
            if not (file.endswith(".c") or file.endswith(".h")):
                continue
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    line_count = sum(1 for _ in f)
                    if line_count >= min_lines:
                        rel_path = os.path.relpath(file_path)
                        if rel_path not in printed_dirs:
                            print(rel_path)
                            printed_dirs.add(rel_path)
            except Exception as e:
                print(f"Could not read {file_path}: {e}")

# Run the function
find_directories_with_largest_files()
