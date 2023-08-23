#WILLIAN GUSTAVO
#PRONTUARIO: BI3003965

import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import cv2 as cv
from scipy import ndimage

def main():
    img = Image.open('lena_gray_512_salt_pepper.tif')

    # Rotação com Numpy
    numpy_90 = np.rot90(img)

    # Rotação com Pillow
    pillow_100 = img.rotate(100) 
    pillow_90 = img.rotate(90)
    pillow_45 = img.rotate(45)

    # Rotação com OpenCV
    img = cv.imread("lena_gray_512_salt_pepper.tif")
    width, height = img.shape[:2]
    ponto = (width / 2, height / 2)
    rotacao = cv.getRotationMatrix2D(ponto, 45, 1.0)
    opencv_45 = cv.warpAffine(img, rotacao, (width, height))

    opencv_90 = cv.rotate(img, cv.ROTATE_90_COUNTERCLOCKWISE)

    rotacao = cv.getRotationMatrix2D(ponto, 100, 1.0)
    opencv_100 = cv.warpAffine(img, rotacao, (width, height))

    # Rotação com Scipy
    scipy_45 = ndimage.rotate(img, 45, reshape=False)
    scipy_90 = ndimage.rotate(img, 90, reshape=False)
    scipy_100 = ndimage.rotate(img, 100, reshape=False)

    fig, ax = plt.subplots(nrows=4, ncols=4)
    ax[0,0].imshow(img, cmap='gray')
    ax[0,0].set_title("Imagem Original")
    ax[0,1].imshow(pillow_45, cmap='gray')
    ax[0,1].set_title("Rotacionada a 45 graus")
    ax[0,2].imshow(numpy_90, cmap='gray')
    ax[0,2].set_title("Rotacionada a 90 graus")
    ax[0,3].imshow(pillow_100, cmap='gray')
    ax[0,3].set_title("Rotacionada a 100 graus")

    ax[1,0].imshow(img, cmap='gray')
    ax[1,0].set_title("Imagem Original")
    ax[1,1].imshow(pillow_45, cmap='gray')
    ax[1,1].set_title("Rotacionada a 45 graus")
    ax[1,2].imshow(pillow_90, cmap='gray')
    ax[1,2].set_title("Rotacionada a 90 graus")
    ax[1,3].imshow(pillow_100, cmap='gray')
    ax[1,3].set_title("Rotacionada a 100 graus")

    ax[2,0].imshow(img, cmap='gray')
    ax[2,0].set_title("Imagem Original")
    ax[2,1].imshow(opencv_45, cmap='gray')
    ax[2,1].set_title("Rotacionada a 45 graus")
    ax[2,2].imshow(opencv_90, cmap='gray')
    ax[2,2].set_title("Rotacionada a 90 graus")
    ax[2,3].imshow(opencv_100, cmap='gray')
    ax[2,3].set_title("Rotacionada a 100 graus")

    ax[3,0].imshow(img, cmap='gray')
    ax[3,0].set_title("Imagem Original")
    ax[3,1].imshow(scipy_45, cmap='gray')
    ax[3,1].set_title("Rotacionada a 45 graus")
    ax[3,2].imshow(scipy_90, cmap='gray')
    ax[3,2].set_title("Rotacionada a 90 graus")
    ax[3,3].imshow(scipy_100, cmap='gray')
    ax[3,3].set_title("Rotacionada a 100 graus")
    plt.show()




if __name__ == "__main__":
    main()