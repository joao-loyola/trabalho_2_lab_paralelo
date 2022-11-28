from os import times_result
import pandas as pd

df = pd.read_csv("time_result.csv")

with open("results.txt", "a") as f:
    linha = str(df.tempo.mean()) + " + " + str(2 * df.tempo.std()) + "\n"
    f.write(linha)
