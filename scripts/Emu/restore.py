import os


def find_files(filename, search_path):
    result = []
    for root, dir, files in os.walk(search_path):
        if filename in files:
            result.append(os.path.join(root, filename))
    return result

def restore(target, backup):
    print(f"Reading backup {backup}")
    with open(backup, "r") as f:
        data = f.read()
    print(f"Restoring backup to {target}\n")
    with open(target, "w") as f:
        f.write(data)

    os.remove(backup)


nameTarget = "N5110.h"
backupNameTarget = "N5110.bak"
backups = find_files(backupNameTarget, "./")
origs = find_files(nameTarget, "./")
if len(backups) > 0:
    backupNameTarget = backups[0]
    nameTarget = origs[0]
    print(f"\nRestoring {backupNameTarget} to {nameTarget}")
    restore(nameTarget, backupNameTarget)


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
    restore(cpp, dupcpp)
else:
    print(f"Backup file not found")
    print(f"Ending\n")