#!/bin/env/python3
import requests


response = requests.get('https://www.coinexchange.io/api/v1/getmarkets')
data = response.json()

result = data["result"]
print(len(result))
f = open("dictionnary.txt","w")
for elt in result:
    f.write((elt["MarketAssetName"].replace(" ","")+"\n").lower())
f.close()
