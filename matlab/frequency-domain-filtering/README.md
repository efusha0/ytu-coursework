# 📡 Frequency Domain Image Filtering (2D-FFT Denoising)

This project demonstrates the practical application of the Two-Dimensional Fast Fourier Transform (2D-FFT) to analyze an image corrupted by periodic sinusoidal noise in the frequency domain, design a custom frequency domain filter (Notch/Band-stop filter), and reconstruct a cleaned version of the image.

## 📌 About the Project

When digital images (such as scanned archival documents, vehicle license plates, QR codes, or satellite images) are acquired, they can suffer from periodic interference caused by scanner sensors, camera systems, or electrical noise. While these periodic patterns (e.g., horizontal/vertical lines, regular waves, or *moiré* patterns) are exceptionally difficult to isolate and remove directly in the **Spatial Domain**, they manifest as distinct, symmetrical bright peak points in the **Frequency Domain**.

In this project, a noisy grayscale image is transformed into the frequency domain, the exact spatial frequencies of the periodic noise are identified, and a custom frequency filter mask is designed to attenuate these peaks without destroying the underlying image details.

### 🧮 Mathematical Model
The corrupted image is mathematically modeled as:

$$S(x,y) = I(x,y) + A\cos\left(2\pi(u_0 x + v_0 y)\right)$$

Where $S(x,y)$ represents the noisy image, $I(x,y)$ is the clean original image, $A$ is the noise amplitude, and $u_0$ and $v_0$ are the spatial frequency components of the noise.

The filtering operation in the frequency domain is expressed as:

$$G(u,v) = F(u,v) \cdot H(u,v)$$

Where $F(u,v)$ is the Fourier transform of the noisy image, $H(u,v)$ is the designed filter mask, and $G(u,v)$ is the filtered spectrum.

---

## ⚙️ How the Script Works

`notch_filter_fft.m` runs the whole pipeline:

1. Reads `noisy_image.png`, converts it to grayscale if needed and normalizes it to `double`.
2. Computes the 2D FFT and centers the spectrum with `fftshift`.
3. Builds the log-magnitude spectrum $\log(1 + |F(u,v)|)$ so the noise peaks become visible.
4. Ignores a 30-pixel radius around the DC component and marks every point above 75% of the remaining maximum as a noise peak.
5. Builds an ideal notch mask that zeroes a 4-pixel radius around each detected peak.
6. Applies the mask, shifts back with `ifftshift`, takes the real part of the inverse FFT and normalizes the result.
7. Plots the noisy image, both spectra, the detected peaks, the mask, the filtered spectrum and the cleaned image.

## 📁 Files

| File | Description |
| :--- | :--- |
| `notch_filter_fft.m` | The MATLAB script |
| `noisy_image.png` | Input image corrupted by diagonal periodic noise |
| `image.png` | The same scene without the periodic noise, for visual comparison |

## ▶️ How to Run

Requires MATLAB with the Image Processing Toolbox. Open this folder in MATLAB and run:

```matlab
notch_filter_fft
```

The script prints the coordinates of the detected noise peaks and opens two figures. Console messages and plot titles are in Turkish.
