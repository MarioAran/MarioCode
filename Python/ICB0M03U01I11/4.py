#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 11:06:02 2021

@author: mario
"""

cadena = input('Frase: ').strip().lower()


primeraLetra = cadena[0:1].upper()
restaCadena = cadena[1:len(cadena)]

cadenaFinal = primeraLetra+restaCadena

print(cadenaFinal)
