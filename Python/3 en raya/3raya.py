
def colocarFicha():
    print("dame ficha")
    #fila=input("Fila")
   # columna=input("Columna")


jugador1=input("nombre de jugador")
jugador2=input("nombre de jugador")
fichasEnTeblero=0

continuar = True
while continuar:
    print("dame la posicion de una ficha")
  
    colocarFicha()
    fichasEnTeblero+=1
    if(fichasEnTeblero==9):
        continuar=False