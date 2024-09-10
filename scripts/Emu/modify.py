import os

def find_files(filename, search_path):
    result = []
    for root, dir, files in os.walk(search_path):
        if filename in files:
            result.append(os.path.join(root, filename))
    return result


cpp = "main.cpp"
dupcpp = "main.bak"

placeholder = "NAMEPLACEHOLDER"
targetFile = "N5110.h"
backupTargetFile = "N5110.bak"

lcds = find_files(targetFile, "./")
if len(lcds) > 0:
    targetFile = lcds[0]
    name = input("\nPlease enter the name of your game: ")
    print(f"Reading {targetFile}")
    with open(targetFile, "r") as f:
        data = f.read()
        f.close()
    backupTargetFile = targetFile.replace("N5110.h", backupTargetFile)
    print(f"Backing up {targetFile} to {backupTargetFile}")
    with open(backupTargetFile, "w") as f:
        f.write(data)
        f.close()
        print(f"Backed up successfully")
    data = data.replace(placeholder, name)
    print(f"Modifying {targetFile}")
    with open(targetFile, "w") as f:
        f.write(data)
        f.close()
else:
    print(f"Emulator files not found, please check environment")

print(f"Checking for existing backup file: {dupcpp}")
dups = find_files(dupcpp, "./")
if len(dups) > 0:
    dupcpp = dups[0]
    print(f"Backup file already exists at: {dupcpp}")
    validAns = {"yes", "y", "no", "n"}
    userInput = ""
    while userInput.lower() not in validAns:
        userInput = input("Would you like to restore existing backup file before continuing? (yes/no): ")
    if userInput.lower() in {"yes", "y"}:
        print(f"Reading backup {dupcpp}")
        with open(dupcpp, "r") as f:
            data = f.read()
            f.close()
        print(f"Restoring backup to {cpp}\n")
        with open(cpp, "w") as f:
            f.write(data)
            f.close()

        os.remove(dupcpp)

print(f"\nSearching for file: {cpp}")
cpp = find_files(cpp, "./")[0]

print(f"Found here: {cpp}")

print(f"Reading {cpp}")
with open(cpp, 'r') as f:
    data = f.read()
    f.close()

print(f"Backing up {cpp} to {dupcpp}")
with open(dupcpp, 'w') as f:
    f.write(data)
    f.close()
    print(f"Backed up successfully")

includeAndCreate = "#include \"SDLInputHandling.h\"\nSDLInputHandling inputs;\n"

oldTxt = "while("
oldTxtAlt = "while ("
newTxt = "while(!inputs.checkInputs() && "

# oldMain = "int main() {"
# oldMainAlt = "int main(){"
# newMain = "int main(int argc, char* argv[]) {\n\tSDLInputHandling inputs;\n"

data = data.replace(oldTxt, newTxt)
data = data.replace(oldTxtAlt, newTxt)

# data = data.replace(oldMain, newMain)
# data = data.replace(oldMainAlt, newMain)

print(f"Modifying {cpp}\n")
with open(cpp, 'w') as f:
    f.write(includeAndCreate)
    f.write(data)
    f.close()
