pa = int(input('Barres Pa: '))
preuPa = float(input('Preu Pa: '))

total = pa * preuPa

if total < 3.0 :
    llet = int(input('Brics LLet: '))
    preuLlet= float(input('Preu Llet: '))

total = total + (llet*preuLlet)

print('Total Compra:', total)