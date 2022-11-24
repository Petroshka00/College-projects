# Hacer un programa que tome los pixeles de una imagen y los
# ordene segun cierto parametro
from PIL import Image
from numpy import sort

im = Image.open('4k.jpg')                   #Cargar la imagen y determinar ciertos parametros
imrgb = im.convert("RGB")                   #Como la altura, ancho y otras variables/constantes
mapapixel = imrgb.load()
width = imrgb.width
height = imrgb.height
temp = ()
pixels = []
todospixels = []


for i in range(0, int(height)):
    for j in range(0, int(width)):          #Conseguir cada valor de RGB de cada pixel
        temp = imrgb.getpixel((j ,i))
        pixels += [x for x in temp]


for i in range(0, len(pixels) - 2, 3):
    nuevopixel = []
    nuevopixel.append(pixels[i+0])          #Separar cada valor RGB como item en una lista
    nuevopixel.append(pixels[i+1])          #Y agregarlo a otra lista como lista de listas
    nuevopixel.append(pixels[i+2])
    todospixels.append(nuevopixel)

todospixels = sorted(todospixels)      #Ordena los pixeles segun brillosidad (promedio de rgb)
todospixels = todospixels[::-1]        

for y in range(0, int(height)):
    for x in range(0, int(width)):                                  #Reasignar los valores de cada pixel
        mapapixel[x, y] = tuple(todospixels[x + y * width])         #Para producir la nueva imagen ordenada

imrgb.show()