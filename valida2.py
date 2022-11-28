with open("output.txt","r") as f1:
    with open("ordered.txt","r") as f2:
        valores = list(map(int, f1.readline().split("  ")[:-1]))
        ordenado = list(map(int, f2.readline().split("  ")[:-1]))
        for i, j in zip(valores, ordenado):
            if i != j:
                print("Não ordenada")
                exit()
print("Ordenada")