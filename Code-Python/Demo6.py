import cv2
import numpy as np
import matplotlib.pyplot as plt

def rgb_to_cmy(image):
    return 255 - image

def rgb_to_cmyk(image):
    img = image.astype(float)
    K = 255 - np.max(img, axis=2)
    C = 255 * (1 - img[..., 2] / 255 - K / 255) / (1 - K / 255 + 1e-7)
    M = 255 * (1 - img[..., 1] / 255 - K / 255) / (1 - K / 255 + 1e-7)
    Y = 255 * (1 - img[..., 0] / 255 - K / 255) / (1 - K / 255 + 1e-7)
    CMYK = cv2.merge((C.astype(np.uint8), M.astype(np.uint8), Y.astype(np.uint8), K.astype(np.uint8)))
    return CMYK

def rgb_to_hsi(image):
    img = image.astype('float32') / 255
    B, G, R = cv2.split(img)
    num = 0.5 * ((R - G) + (R - B))
    den = np.sqrt((R - G)**2 + (R - B)*(G - B)) + 1e-7
    theta = np.arccos(num / den)
    H = np.where(B <= G, theta, 2*np.pi - theta)
    H = H / (2*np.pi)
    S = 1 - (3 / (R + G + B + 1e-7)) * np.minimum(np.minimum(R, G), B)
    I = (R + G + B) / 3
    HSI = cv2.merge((H, S, I))
    return (HSI * 255).astype(np.uint8)

def rgb_to_yuv(image):
    img = image.astype('float32')
    transform = np.array([[ 0.299,  0.587,  0.114],
                          [-0.14713, -0.28886, 0.436],
                          [ 0.615, -0.51499, -0.10001]])
    yuv = img @ transform.T
    return np.clip(yuv, 0, 255).astype(np.uint8)

def rgb_to_ycbcr(image):
    img = image.astype('float32')
    R = img[..., 2]
    G = img[..., 1]
    B = img[..., 0]
    Y  =  0.299 * R + 0.587 * G + 0.114 * B
    Cb = -0.168736 * R - 0.331264 * G + 0.5 * B + 128
    Cr =  0.5 * R - 0.418688 * G - 0.081312 * B + 128
    return cv2.merge((Y, Cb, Cr)).astype(np.uint8)

def smoothing(image):
    return cv2.GaussianBlur(image, (5, 5), 0)

def sharpening(image):
    kernel = np.array([[0, -1, 0],
                       [-1, 5,-1],
                       [0, -1, 0]])
    return cv2.filter2D(image, -1, kernel)

def show_image(title, image):
    plt.figure(figsize=(5,5))
    plt.title(title)
    if image.ndim == 2 or image.shape[2] == 1:
        plt.imshow(image, cmap='gray')
    else:
        plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    plt.axis('off')
    plt.show()

# --- LOAD GAMBAR ---
image = cv2.imread('mandril_color.jpg')

# --- PROSES KONVERSI WARNA DAN FILTER ---
cmy = rgb_to_cmy(image)
cmyk = rgb_to_cmyk(image)
hsi = rgb_to_hsi(image)
yuv = rgb_to_yuv(image)
ycbcr = rgb_to_ycbcr(image)
smooth = smoothing(image)
sharp = sharpening(image)

# --- TAMPILKAN HASIL ---
show_image('Original (RGB)', image)
show_image('CMY', cmy)
show_image('CMYK', cmyk)
show_image('HSI', hsi)
show_image('YUV', yuv)
show_image('YCbCr', ycbcr)
show_image('Smoothing (Gaussian Blur)', smooth)
show_image('Sharpening (Laplacian)', sharp)