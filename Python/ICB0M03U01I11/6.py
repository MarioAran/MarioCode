#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 11:15:39 2021

@author: mario
"""
dies = ['dl','dm','dc','dj','dv']
cadena = input('Cadena: ').lower()
correcte = False 

for x in dies:
    if cadena == x:
        correcte = True 


print(correcte)