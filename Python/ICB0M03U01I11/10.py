#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 11:36:13 2021

@author: mario
"""

dias = [31,28,31,30,31,30,31,31,30,31,30,31]
data = input('Data: ')
x = data.split("/")
mes = int(x[1])-1

if int(x[0]) <= dias[mes]:
    print('Correcte')
else: 
    print('Incorrecte')