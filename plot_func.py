import matplotlib.pyplot as plt
from const import fs, Fs, D, t, A_input, td, T

def to_plot(sig, buf_lpf1_0, buf_lpf1_90, pll_buf0, buf_y9, pll_buf90, buf_y10):

    ax1 = plt.subplot(511)
    ax2 = plt.subplot(512, sharex=ax1)
    ax3 = plt.subplot(513, sharex=ax1)
    ax4 = plt.subplot(514, sharex=ax1)
    ax5 = plt.subplot(515, sharex=ax1)

    ax1.plot(t,sig)
    #ax1.plot(t,buf_gen0)
    #ax1.plot(t,buf_gen90)
    #ax1.grid(True)

    ax2.plot(t,buf_lpf1_90)
    #ax1.plot(t,buf_mux1_90)
    ax1.grid(True)

    ax2.plot(t,buf_lpf1_0)
    #ax2.plot(t,buf_mux1_0)
    ax2.grid(True)


    ax3.plot(td,pll_buf0)
    ax3.plot(td,buf_y9)
    #ax3.grid(True)

    ax4.plot(td,pll_buf90)
    ax4.plot(td,buf_y10)
    #ax4.grid(True)

    plt.show()
# *--------------------------------------------------------------------------
