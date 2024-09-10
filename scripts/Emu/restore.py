import os


def find_files(filename, search_path):
    result = []
    for root, dir, files in os.walk(search_path):
        if filename in files:
            result.append(os.path.join(root, filename))
    return result


dupcpp = "main.bak"
cpp = "main.cpp"
print(f"\nFinding file {cpp}")
cpp = find_files(cpp, "./")[0]
print(f"Found at {cpp}")
print(f"Finding backup file {dupcpp}")
dups = find_files(dupcpp, "./")

if len(dups) > 0:
    dupcpp = dups[0]
    print(f"Found at {dupcpp}")
    print(f"Reading backup {dupcpp}")
    with open(dupcpp, "r") as f:
        data = f.read()
    print(f"Restoring backup to {cpp}\n")
    with open(cpp, "w") as f:
        f.write(data)

    os.remove(dupcpp)
else:
    print(f"Backup file not found")
    print(f"Ending\n")