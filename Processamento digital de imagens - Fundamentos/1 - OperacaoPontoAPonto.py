#WILLIAN GUSTAVO
#PRONTUARIO: BI3003965

import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

width = 10
height = 5
image_matrix = np.zeros([height, width])



def main():
    img = Image.open('lena_gray_512.tif')
    print(img.format)
    print(img.size)
    print(img.mode)
    #img.show() #plota imagem usando o pillow
    npImg = np.array(img) #CONVERTE IMAGEM PARA UM ARRAY NUMPY
    npImg = 255 - npImg #Negativo
    npImg =  (npImg / 2).astype(int) #Divindo pixels
    
    #criando quadrados brancos 10x10 em cada canto da imagem
    npImg[0:10,0:10] = 255
    npImg[502:512,0:10] = 255
    npImg[0:10,502:512] = 255
    npImg[502:512,502:512] = 255
    
    #criando quadrado branco 15x15 no centro da imagem
    altura = npImg.shape[0]
    l  = npImg.shape[1]
    
    npImg[round(altura/2)-7:round(altura/2)+8, round(l/2)-7:round(l/2)+8] = 255
    
    imgNew = Image.fromarray(npImg)
    #imgNew.show()
    #plotar usando o matplotlib
    fig, ax = plt.subplots(nrows=1,ncols=2)
    ax[0].imshow(img, cmap="gray")
    ax[0].set_title("Imagem original")
    ax[1].imshow(imgNew, cmap="gray")
    ax[1].set_title("Imagem filtrada")
    plt.show()
    #print(type(npImg))
    
if __name__== "__main__":
    main()