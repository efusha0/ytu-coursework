# 📡 Frequency Domain Image Filtering (2D-FFT Denoising)

This project demonstrates the practical application of the Two-Dimensional Fast Fourier Transform (2D-FFT) to analyze an image corrupted by periodic sinusoidal noise in the frequency domain, design a custom frequency domain filter (Notch/Band-stop filter), and reconstruct a cleaned version of the image.

## 📌 About the Project

When digital images (such as scanned archival documents, vehicle license plates, QR codes, or satellite images) are acquired, they can suffer from periodic interference caused by scanner sensors, camera systems, or electrical noise. While these periodic patterns (e.g., horizontal/vertical lines, regular waves, or *moiré* patterns) are exceptionally difficult to isolate and remove directly in the **Spatial Domain**, they manifest as distinct, symmetrical bright peak points in the **Frequency Domain**.

In this project, a noisy grayscale image is transformed into the frequency domain, the exact spatial frequencies of the periodic noise are identified, and a custom frequency filter mask is designed to attenuate these peaks without destroying the underlying image details.

### 🧮 Mathematical Model
The corrupted image is mathematically modeled as:
S(x,y) = I(x,y) + A\cos(2\pi(u_0x + v_0y))

Where S(x,y) represents the noisy image, I(x,y) is the clean original image, A is the noise amplitude, and u_0 and v_0 are the spatial frequency components of the noise.

The filtering operation in the frequency domain is expressed as:
G(u,v) = F(u,v) \cdot H(u,v)

Where F(u,v) is the Fourier transform of the noisy image, H(u,v) is the designed filter mask, and G(u,v) is the filtered spectrum.
