vehicle = input('Vehicle (C/M): ').upper()
km = float(input('KM:  '))

def getprice (vehicle):
    preu = float
    
    if vehicle == 'C' :
        preu = 0.06

    if vehicle == 'M' :
        preu = 0.02
    
    return preu

precio = getprice(vehicle)

gasolina = precio * km 

print(gasolina)



