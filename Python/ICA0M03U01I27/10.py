def rango(edad):
    if edad >=16 and edad <= 18:
        rango =0
    elif edad >18  and edad < 22:
        rango =1
    elif edad >= 22 and edad <= 30:
        rango =2
    elif edad > 30:
        rango =3
    return rango

edad = int(input('Edad: '))
if edad >0:
    carnet= int(input('Anys Carnet: '))
    if carnet >0:
        socio= input('Soci (S/N): ')
        precio = [175,125,110,100]
        precioSeguro = precio[rango(edad)]
        precioPenalizacion = 50 

        for x in range(carnet-4):
            precioPenalizacion =precioPenalizacion-10
        
            if precioPenalizacion == 0:
                precioPenalizacion == 0 
        
        precioTotal = precioSeguro + precioPenalizacion
        
        if socio.upper() == 'S':
            precioTotal = precioTotal - (precioTotal * 0.10)
        print(precioTotal)
        
    else:
        print('Error')    
else: 
    print('Error')