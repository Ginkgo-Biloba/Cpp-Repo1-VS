from typing import List
import collections


def ad(a, b):
	return collections.Counter(a) + collections.Counter(b)

print(ad([1, 2], [2, 2]))
