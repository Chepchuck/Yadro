inp = []
with open("output_merged.bin", "rb") as f, open("input.bin", "rb") as res:
    print("Sorted by C++ app:")
    for _ in range(200):
        print(int.from_bytes(f.read(4), "little", signed=True), end=" ")
    for _ in range(200):
        inp.append(int.from_bytes(res.read(4), "little", signed=True))
    print("\nSorted input values by python:")
    print(sorted(inp), sep=" ")