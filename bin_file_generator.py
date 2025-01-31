import struct
import random

# Имя файла
filename = 'input.bin'

result = []
#Открываем файл для записи в бинарном режиме
with open(filename, 'wb') as f, open("result.txt", "w") as t:
    for _ in range(200):
        value = random.randint(-0x80000000, 0x7FFFFFFF)  # -2³¹ до 2³¹ - 1
        print(value, file=t, end=" ")
        f.write(struct.pack('<i', value))  # 4 байта (little-endian)

print(f"Файл '{filename}' успешно создан.")


# with open("output_merged", "rb") as f, open("input.bin", "rb") as res:
#     for _ in range(200):
#         print(int.from_bytes(f.read(4), "little"), end=" ")
#     print("\nSorted:")
#     for _ in range(200):
#         print(int.from_bytes(res.read(4), "little"), end=" ")
#     print()