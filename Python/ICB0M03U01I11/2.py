#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 10:58:55 2021

@author: mario
"""

cadena  = input('Frase: ')
cadena  = cadena.strip()
primera = cadena[0:1]
segona  = cadena[len(cadena)-1:len(cadena)]

print(primera)
print(segona)

