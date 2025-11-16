import os
import re

def find_large_c_functions(base_dir='.', line_limit=50):
    function_pattern = re.compile(r'^[\w\s\*\(\)]+?\s+(\w+)\s*\([^)]*\)\s*{')
    
    for root, _, files in os.walk(base_dir):
        for file in files:
            if file.endswith('.c'):
                path = os.path.join(root, file)
                with open(path, 'r', errors='ignore') as f:
                    lines = f.readlines()

                inside_function = False
                brace_count = 0
                start_line = 0
                func_name = ""
                for i, line in enumerate(lines):
                    stripped = line.strip()

                    # Try to detect function start
                    if not inside_function:
                        match = function_pattern.match(stripped)
                        if match and not stripped.startswith('//'):
                            func_name = match.group(1)
                            inside_function = True
                            brace_count = line.count('{') - line.count('}')
                            start_line = i
                    else:
                        # Count braces
                        brace_count += line.count('{') - line.count('}')
                        if brace_count <= 0:
                            inside_function = False
                            length = i - start_line + 1
                            if length > line_limit:
                                rel_path = os.path.relpath(path)
                                print(f"{rel_path}:{start_line + 1} -> {func_name} ({length} lines)")

if __name__ == "__main__":
    find_large_c_functions()
