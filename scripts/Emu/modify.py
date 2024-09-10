import os

def find_files(filename, search_path):
    result = []
    for root, dir, files in os.walk(search_path):
        if filename in files:
            result.append(os.path.join(root, filename))
    return result



cpp = "main.cpp"
dupcpp = "main.bak"

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
