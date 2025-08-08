import os
import re

def find_global_variables(root_dir):
    """Find all global variables in C files within a directory tree."""
    global_vars = []
    
    # Simplified regular expression to match global variable declarations
    # This pattern will catch most common cases but may need adjustment
    pattern = re.compile(
        r'^(?!(?:#if|#endif|#define|#include)\b)'  # Skip preprocessor directives
        r'(?!(?:\s*\/\/|\/\*))'  # Skip comments
        r'(?:[a-zA-Z_][a-zA-Z0-9_]*\s+)+'  # Type specifier
        r'(?:\*\s*)?'  # Optional pointer
        r'[a-zA-Z_][a-zA-Z0-9_]*'  # Variable name
        r'(?:\s*\[\s*\d*\s*\])*'  # Optional array
        r'(?:\s*=\s*[^;]+)?'  # Optional initialization
        r'\s*;',  # Semicolon
        re.MULTILINE
    )
    
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file.endswith(('.c', '.h', '.cpp', '.hpp')):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                        
                        # Remove comments to avoid false positives
                        content = re.sub(r'//.*', '', content)
                        content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
                        
                        # Split into lines while preserving line numbers
                        lines = content.split('\n')
                        
                        for line_num, line in enumerate(lines, 1):
                            line = line.strip()
                            if pattern.match(line):
                                global_vars.append({
                                    'file': filepath,
                                    'line': line_num,
                                    'variable': line
                                })
                except Exception as e:
                    print(f"Error processing {filepath}: {str(e)}")
    
    return global_vars

def print_global_variables(global_vars):
    """Print the found global variables in a readable format."""
    if not global_vars:
        print("No global variables found.")
        return
    
    print("\nGlobal Variables Found:")
    print("======================")
    
    current_file = None
    for var in sorted(global_vars, key=lambda x: x['file']):
        if var['file'] != current_file:
            current_file = var['file']
            print(f"\nFile: {current_file}")
            print("-" * (len(current_file) + 7))
        
        print(f"Line {var['line']}: {var['variable']}")

if __name__ == "__main__":
    project_dir = input("Enter the path to your C project directory: ").strip()
    
    if not os.path.isdir(project_dir):
        print(f"Error: '{project_dir}' is not a valid directory.")
    else:
        print(f"Searching for global variables in {project_dir}...")
        globals_list = find_global_variables(project_dir)
        print_global_variables(globals_list)