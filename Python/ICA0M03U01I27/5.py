import statistics as stats

nota = ['A','B','C','D','E']
valor= [9.5,6.7,5.3,3.6,1]

def getValor(notaAlumno):
    notaFinal = float
    for x in range(len(nota)):
        if nota[x] == notaAlumno:
            notaFinal = valor[x]
    return notaFinal
##pedir notas
nota1 = input('Nota1: ').upper()
nota2 = input('Nota2: ').upper()
##Obtener valor notas
nota1valor = getValor(nota1)
nota2valor = getValor(nota2)
#crear array con notas y obtener la media
media = [nota1valor, nota2valor]
notaFinal = stats.mean(media)

##imprimir datos
print(notaFinal)
if notaFinal > 8 : 
    print('Felicidades')