import cv2
import numpy as np
import matplotlib.pyplot as plt

# 1. Load citra grayscale
img = cv2.imread('mandril_color.jpg', cv2.IMREAD_GRAYSCALE)

# 2. Histogram Equalization
hist_eq = cv2.equalizeHist(img)

# 3. Spatial Smoothing (Filter rata-rata 3x3)
kernel_smooth = np.ones((3, 3), np.float32) / 9
smooth_img = cv2.filter2D(img, -1, kernel_smooth)

# 4. Spatial Sharpening (menggunakan kernel Laplacian)
kernel_sharp = np.array([[0, -1, 0],
                         [-1, 5, -1],
                         [0, -1, 0]])
sharp_img = cv2.filter2D(img, -1, kernel_sharp)

# 5. Tampilkan hasil
titles = ['Original Grayscale', 'Histogram Equalization', 'Spatial Smoothing', 'Spatial Sharpening']
images = [img, hist_eq, smooth_img, sharp_img]

plt.figure(figsize=(10, 8))
for i in range(4):
    plt.subplot(2, 2, i + 1)
    plt.imshow(images[i], cmap='gray')
    plt.title(titles[i])
    plt.axis('off')

plt.tight_layout()
plt.show()
