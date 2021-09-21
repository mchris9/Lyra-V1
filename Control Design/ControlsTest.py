import numpy as np
import control.matlab as ml
import matplotlib.pyplot as plt

num = np.array([1])
den = np.array([1,40000,8912492836])

G = ml.tf(num,den)

mag, phase, omega = ml.bode(G)
plt.show()