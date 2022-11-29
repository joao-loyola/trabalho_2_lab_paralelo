# calcula média e desvio padrão do tempo
import pandas as pd

df = pd.read_csv("time_result.csv")
print(df.tempo.mean(), '+', 2 * df.tempo.std())
