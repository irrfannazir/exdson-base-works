import os

def search_word_in_files(base_dir, word):
    for root, _, files in os.walk(base_dir):
        for filename in files:
            if filename.endswith(('.c', '.h')):
                filepath = os.path.join(root, filename)
                try:
                    with open(filepath, 'r', errors='ignore') as file:
                        for line_number, line in enumerate(file, start=1):
                            if word in line:
                                rel_path = os.path.relpath(filepath, base_dir)
                                print(f"{rel_path}:{line_number}: {line.strip()}")
                except Exception as e:
                    print(f"Could not read {filepath}: {e}")

# --- Edit these ---
search_directory = "."         # Current directory
search_word = input()            # Word you want to find

# --- Run search ---
search_word_in_files(search_directory, search_word)
