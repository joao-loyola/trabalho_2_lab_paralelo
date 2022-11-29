with open("time_result.csv","r") as f:
    soma = 0
    df = f.readlines()
    tam = ( len(df))
    for i in (df):
        soma+= float(i[:-1])
    
    # valores = list( map(float, f.readline().split("  ")[:-1]))
    # # print(sorted(valores))
    # temp = valores[0]
    print(soma/tam)
# print("Ordenada")
