import re
import os

# --- EXTRACTION LOGIC ---

def extract_whole(content):
    return content

def extract_include(content, name):
    pattern = re.compile(rf'^\s*#include\s+["<]{re.escape(name)}[">].*', re.MULTILINE)
    match = pattern.search(content)
    if match:
        return match.group(0).strip()
    return None

def extract_region(content, name):
    start_pattern = re.compile(rf'//\s*region:\s*{re.escape(name)}\s*$', re.MULTILINE)
    end_pattern = re.compile(r'//\s*endregion', re.MULTILINE)
    
    start_match = start_pattern.search(content)
    if not start_match: return None
    
    start_idx = start_match.end()
    end_match = end_pattern.search(content, start_idx)
    
    if not end_match: return None
    
    snippet = content[start_idx : end_match.start()]
    
    lines = snippet.split('\n')
    if lines and not lines[0].strip(): lines.pop(0)
    if lines and not lines[-1].strip(): lines.pop()
    
    return '\n'.join(lines)

def extract_define(content, name):
    pattern = re.compile(rf'(#define\s+{re.escape(name)}\b.*)', re.MULTILINE)
    match = pattern.search(content)
    return match.group(1) if match else None

def extract_struct(content, name):
    pattern_def = re.compile(rf'struct\s+{re.escape(name)}\s*\{{', re.DOTALL)
    match_def = pattern_def.search(content)
    
    if match_def:
        start_idx = match_def.start()
        open_brace_idx = match_def.end() - 1
        idx = open_brace_idx + 1
        balance = 1
        
        while idx < len(content):
            if content[idx] == '{': balance += 1
            elif content[idx] == '}': balance -= 1
            
            if balance == 0:
                end_idx = idx + 1
                while end_idx < len(content):
                    char = content[end_idx]
                    if char == ';':
                        end_idx += 1
                        break
                    if not char.isspace():
                        end_idx = idx + 1
                        break
                    end_idx += 1
                return content[start_idx : end_idx]
            idx += 1

    pattern_fwd = re.compile(rf'struct\s+{re.escape(name)}\s*;')
    match_fwd = pattern_fwd.search(content)
    if match_fwd:
        return match_fwd.group(0)

    return None

def extract_typedef(content, name):
    pattern_block = re.compile(r'\}\s*' + re.escape(name) + r'\s*;')
    match = pattern_block.search(content)
    if match:
        end_idx = match.end()
        idx = match.start()
        balance = 0
        while idx >= 0:
            char = content[idx]
            if char == '}': balance += 1
            elif char == '{': balance -= 1
            if balance == 0 and char == '{':
                preamble_start = max(0, idx - 200)
                preamble = content[preamble_start:idx]
                t_match = re.search(r'typedef\s+(struct|union|enum)', preamble)
                if t_match:
                    real_start = preamble_start + t_match.start()
                    return content[real_start:end_idx]
            idx -= 1

    pattern_simple = re.compile(rf'(typedef\s+(?:(?!;).)*\b{re.escape(name)}\s*;)', re.DOTALL)
    match_simple = pattern_simple.search(content)
    if match_simple: return match_simple.group(1).strip()
    return None

def extract_function(content, name):
    pattern_impl = re.compile(rf'\b{re.escape(name)}\s*\(.*?\)\s*\{{', re.DOTALL)
    match = pattern_impl.search(content)
    is_prototype = False
    
    if not match:
        pattern_proto = re.compile(rf'\b{re.escape(name)}\s*\(.*?\)\s*;', re.DOTALL)
        match = pattern_proto.search(content)
        is_prototype = True
    
    if not match: return None
    
    start_idx = match.start()
    cursor = start_idx - 1
    definition_start = start_idx 
    
    while cursor >= 0:
        char = content[cursor]
        if char in {';', '}', '{'}: 
            definition_start = cursor + 1
            break
        if char == '\n':
            prev_newline = content.rfind('\n', 0, cursor)
            line_start = prev_newline + 1
            line = content[line_start:cursor].strip()
            if line.startswith('#') or line.startswith('//'):
                definition_start = cursor + 1
                break
        if char == '/' and cursor > 0 and content[cursor-1] == '*':
            definition_start = cursor + 1
            break
        cursor -= 1

    if cursor < 0: definition_start = 0

    snippet = ""
    if is_prototype:
        snippet = content[definition_start : match.end()].strip()
    else:
        open_brace_idx = match.end() - 1
        idx = open_brace_idx + 1
        balance = 1
        while idx < len(content):
            if content[idx] == '{': balance += 1
            elif content[idx] == '}': balance -= 1
            if balance == 0:
                snippet = content[definition_start : idx+1].strip()
                break
            idx += 1

    if snippet:
        snippet = re.sub(
            r'^\s*//\s*(?:region:|endregion).*?(\r?\n|$)', 
            '', 
            snippet, 
            flags=re.MULTILINE
        )
        return snippet.strip()

    return None

def get_snippet(root_dir, rel_path, kind, name):
    full_path = os.path.join(root_dir, rel_path)
    if not os.path.exists(full_path):
        # ERROR: Stop the build immediately
        raise FileNotFoundError(f"Source file not found: {rel_path}")
    
    with open(full_path, 'r', encoding='utf-8') as f:
        content = f.read()

    snippet = None
    if kind == "whole": snippet = extract_whole(content)
    elif kind == "define": snippet = extract_define(content, name)
    elif kind == "typedef": snippet = extract_typedef(content, name)
    elif kind == "function": snippet = extract_function(content, name)
    elif kind == "struct": snippet = extract_struct(content, name)
    elif kind == "include": snippet = extract_include(content, name)
    elif kind == "region": snippet = extract_region(content, name)
    else: 
        raise ValueError(f"Unknown type '{kind}' requested for '{name}'")

    if not snippet:
        # ERROR: Stop the build immediately
        raise ValueError(f"Could not find {kind} '{name}' in {rel_path}")

    return f"```c\n{snippet}\n```"

# --- MAIN PROCESSING ---

def process_markdown_content(text, root_dir):
    tag_pattern = re.compile(r'\{\{\s*file\s*"(.*?)"\s*type="(.*?)"(?:\s*name="(.*?)")?\s*\}\}')
    
    # This will now raise an exception if get_snippet fails
    expanded_text = tag_pattern.sub(
        lambda m: get_snippet(root_dir, m.group(1), m.group(2), m.group(3)), 
        text
    )

    merge_pattern = re.compile(r'```c\n(.*?)\n```\s*```c\n', re.DOTALL)
    
    while True:
        new_text = merge_pattern.sub(r'```c\n\1\n\n', expanded_text)
        if new_text == expanded_text:
            break
        expanded_text = new_text
        
    return expanded_text