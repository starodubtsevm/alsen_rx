from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

fs = 800       # Sample rate, Hz
cutoff = 15.0    # Desired cutoff frequency, Hz
trans_width = 10  # Width of transition from pass band to stop band, Hz
numtaps = 50      # Size of the FIR filter.
taps = signal.remez(numtaps, [0, cutoff, cutoff + trans_width, 0.5*fs], [1, 0], Hz=fs)
w, h = signal.freqz(taps, [1], worN=2000)

fig, ax1 = plt.subplots()
ax1.set_title('Digital filter frequency response')

ax1.plot((fs * 0.5 / np.pi) * w, 20 * np.log10(abs(h)), 'b')
ax1.set_ylabel('Amplitude [dB]', color='b')
ax1.set_xlabel('Frequency [Hz]')

plt.show()
