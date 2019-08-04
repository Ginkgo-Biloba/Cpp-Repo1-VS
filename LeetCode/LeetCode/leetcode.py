import numpy as np
from numpy import linalg

(a, b, c) = (1.44, 0.7, 0.5)
A = np.array([
		[a, b],
		[b, c]
	], np.float64)
e = linalg.eig(A)
print(" ", e[0])
print(e[1])

