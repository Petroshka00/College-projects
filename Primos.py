max = int(input("¿Hasta que numero querés averiguar los numeros primos?: "))
primo = [2, 3, 5, 7]
for i in range(6, max + 1, 6):
    if (i-1) % 5 != 0 and (i-1) % 7 != 0:
        primo.append(i-1)
    if (i+1) % 5 != 0 and (i+1) % 7 != 0:
        primo.append(i+1)
print(primo)