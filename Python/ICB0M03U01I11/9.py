#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 11:31:00 2021

@author: mario
"""

lletra = input('Lletra: ').strip()

if len(lletra) >0 and lletra.isalpha() == True:
    
    if lletra.islower() == True :
        print('MINUSCULA')
    elif lletra.isupper() == True:
        print('MAYUSCULA')

else : 
    print('Error')