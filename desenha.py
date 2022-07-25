from turtle import *
import turtle as tur
import pandas as pd

pontos_df = pd.read_csv("out/desenhar.csv")
numLinhas = pontos_df.shape[0]
inicio = pontos_df.loc[0]

tur.speed(1)
tur.penup()
tur.goto(inicio)
tur.pendown()

for i in range(1,numLinhas):
    tur.goto(pontos_df.loc[i])
    tur.dot()

tur.goto(inicio)
tur.dot()

tur.hideturtle()
tur.exitonclick()
