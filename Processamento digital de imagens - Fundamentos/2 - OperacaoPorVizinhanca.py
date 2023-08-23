#WILLIAN GUSTAVO
#PRONTUARIO: BI3003965

import numpy as np
from PIL import Image, ImageFilter
import matplotlib.pyplot as plt
import cv2 
from scipy import ndimage, misc


def main():
    img = Image.open('lena_gray_512_salt_pepper.tif')
    imgcv = cv2.imread("lena_gray_512_salt_pepper.tif")

    FiltroPillow = img.filter(ImageFilter.MedianFilter(size = 3))
    #FiltroPillow = img.filter(ImageFilter.BoxBlur(3))

    FltroOpenCV = cv2.medianBlur(imgcv,3)
    #FltroOpenCV =  cv2.blur(imgcv,(3,3))

    ascent = misc.ascent()
    Filtroscipy = ndimage.median_filter(ascent, size=20)

    npImgOriginal = np.array(img) #CONVERTE IMAGEM PARA UM ARRAY NUMPY
    width, height = npImgOriginal.shape
    npImgFiltrada = np.zeros((width,height))
    kernel_size = 10 #Tamanho do kernel
    k = int((kernel_size - 1 )/2)
    for row in range(k,height-k):

        for col in range(k,width-k):
            npImgFiltrada[row,col] = np.mean(npImgOriginal[row-k:row+k,col-k:col+k])    #Filtro da media
            #npImgFiltrada[row,col] = np.median(npImgOriginal[row-k:row+k,col-k:col+k])    #Filtro da mediana

    fig, ax = plt.subplots(nrows=3,ncols=2)
    ax[0,0].imshow(npImgOriginal, cmap="gray")
    ax[0,0].set_title("Imagem original")
    ax[0,1].imshow(npImgFiltrada, cmap="gray")
    ax[0,1].set_title("Imagem filtrada com numpy")
    ax[1,0].imshow(FiltroPillow, cmap="gray")
    ax[1,0].set_title("Imagem filtrada com Pillow")
    ax[1,1].set_title("Imagem filtrada com OpenCV")
    ax[1,1].imshow(FltroOpenCV, cmap="gray")
    ax[2,0].set_title("Imagem filtrada com Scipy")
    ax[2,0].imshow(Filtroscipy, cmap="gray")
    ax[2,1].axis('off')
    plt.show()

if __name__== "__main__":
    main()