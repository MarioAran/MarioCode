barres = int(input('Barres de Pa:'))

preuPa = 0.45
preuTotalPa = 0
if barres > 0:
    for x in range(0, barres):
        if x > 5 :
            preuPa=0.40
        if x >= 10:
            preuPa=0.35    
        preuTotalPa= preuTotalPa + preuPa
        print(x , preuPa)
    format_float = "{:.2f}".format(preuTotalPa)
    print(format_float)
else: 
    print('Error Numero Pa')