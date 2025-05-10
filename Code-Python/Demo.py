import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load gambar dan konversi ke grayscale
img = cv2.imread('mandril_color.jpg')
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# --- FORM 1 ---
negative = 255 - gray
log_trans = (255 / np.log(1 + np.max(gray))) * np.log(1 + gray.astype(np.float32))
log_trans = np.array(log_trans, dtype=np.uint8)
gamma = 0.4
gamma_trans = np.power(gray / 255.0, gamma) * 255
gamma_trans = np.array(gamma_trans, dtype=np.uint8)

def piecewise_linear(img):
    r1, s1 = 70, 0
    r2, s2 = 140, 255
    result = np.zeros_like(img)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            r = img[i, j]
            if r < r1:
                result[i, j] = int((s1 / r1) * r)
            elif r <= r2:
                result[i, j] = int(((s2 - s1) / (r2 - r1)) * (r - r1) + s1)
            else:
                result[i, j] = int(((255 - s2) / (255 - r2)) * (r - r2) + s2)
    return result

piecewise = piecewise_linear(gray)

# --- FORM 2: Bit-plane slicing (tampilkan hanya 1 contoh) ---
bit_plane_7 = ((gray >> 7) & 1) * 255

# --- FORM 3: Subtraction ---
bright_img = cv2.convertScaleAbs(img, alpha=0.5, beta=50)
gray2 = cv2.cvtColor(bright_img, cv2.COLOR_BGR2GRAY)
sub_result = cv2.subtract(gray, gray2)

# --- FORM 4: Logika ---
and_result = cv2.bitwise_and(gray, gray2)
or_result = cv2.bitwise_or(gray, gray2)
xor_result = cv2.bitwise_xor(gray, gray2)

# --- TAMPILAN DALAM 3x3 GRID ---
images = [
    ('Grayscale', gray),
    ('Negative', negative),
    ('Log Transform', log_trans),
    ('Gamma Transform', gamma_trans),
    ('Piecewise Linear', piecewise),
    ('Bit-Plane 7', bit_plane_7),
    ('Subtraction', sub_result),
    ('AND', and_result),
    ('OR', or_result),
]

plt.figure(figsize=(12, 12))
for i, (title, img_data) in enumerate(images):
    plt.subplot(3, 3, i + 1)
    plt.imshow(img_data, cmap='gray')
    plt.title(title)
    plt.axis('off')

plt.tight_layout()
plt.show()

# Tampilkan XOR terpisah jika mau
plt.figure(figsize=(4, 4))
plt.imshow(xor_result, cmap='gray')
plt.title('XOR')
plt.axis('off')
plt.show()
