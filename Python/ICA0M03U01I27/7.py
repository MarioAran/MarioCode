pa = int(input('Barres Pa: '))
if pa >= 0 :
    preuPa = float(input('Preu Pa: '))
    total = pa * preuPa

    if total < 3.0 :
        llet = int(input('Brics LLet: '))
        if llet>0:
            preuLlet= float(input('Preu Llet: '))
        else:
            print('Error Llet')
            preuLlet = 0

    total = total + (llet*preuLlet)

    print('Total Compra:', total)
else:
     print('Error Pa')