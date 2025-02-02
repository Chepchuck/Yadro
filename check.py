inp, out = [], []
compare_flag = True
with open("output.bin", "rb") as f, open("input.bin", "rb") as res:
    for _ in range(200):
        out.append(int.from_bytes(f.read(4), "little", signed=True))
        inp.append(int.from_bytes(res.read(4), "little", signed=True))
    print("Sorted by C++ app:")
    print(*out, sep=" ")
    print(f"Sorted input ({len(inp)}) values by python:")
    inp = sorted(inp)
    print(*inp, sep=" ")
    for i in range(len(inp)):
        if inp[i] != out[i] and compare_flag != False:
            compare_flag = False
    print(f"Equals: {compare_flag}")