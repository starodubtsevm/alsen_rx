from scipy.signal import firwin

def bandpass_firwin(ntaps, lowcut, highcut, fs, window='hamming'):
	nyq = 0.5 * fs
	
	taps = firwin(ntaps, highcut, nyq=nyq, pass_zero=True,
		window=window, scale=False)
	return taps

if __name__ == "__main__":
	import numpy as np
	import matplotlib.pyplot as plt
	from scipy.signal import freqz

	# Sample rate and desired cutoff frequencies (in Hz).
	fs = 5000
	fn = fs/2
	lowcut = 2
	highcut = 25

	ntaps = 255
	taps_hamming = bandpass_firwin(ntaps, lowcut, highcut, fs=fs)
	y = []
	x =0
	for i  in range (len(taps_hamming)):
		x = float('{:.5f}'.format(taps_hamming[i]))
		y.append(x)
	
#	print (y)

	# Plot the frequency responses of the filters.
	plt.figure(1, figsize=(12, 9))
	plt.clf()

	# First plot the desired ideal response as a green(ish) rectangle.
	rect = plt.Rectangle((lowcut, 0), highcut - lowcut, -90,
		facecolor="#60ff60", alpha=0.2)
	plt.gca().add_patch(rect)

	# Plot the frequency response of each filter.
	w, h = freqz(y, 1, worN=10000)
	plt.plot((fs * 0.5 / np.pi) * w, 20 * np.log10(abs(h)), label="Hamming window")

	plt.xlim(lowcut - 100, highcut + 100)
	plt.ylim(-90, 5)
	plt.grid(True)
	plt.legend()
	plt.xlabel('Frequency (Hz)')
	plt.ylabel('Gain')
	plt.title('Frequency response of FIR filter, %d taps, fs = %d kHz' % (ntaps, fs))

	plt.show()

