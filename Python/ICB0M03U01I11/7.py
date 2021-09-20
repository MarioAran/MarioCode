#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 11:19:35 2021

@author: mario
"""

cadena = input('Lletra: ')

if len(cadena) > 1: 
    print('Error cadena solo 1 digit')
    
if cadena.isdigit() == True:
    print('Numero')
elif cadena.isalpha() == True:
    print('Lletra')
else: 
    print('Altres')