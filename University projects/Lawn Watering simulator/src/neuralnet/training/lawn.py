import numpy as np
import imageio as imio


class Lawn:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.data = np.zeros((self.height, self.width), dtype=np.uint8)

    def print_lawn(self):
        for i in range(0, self.height, 100):
            for j in range(0, self.width, 100):
                print('#' if self.data[i][j] == 255 else '-', end="")
            print()

    def draw_lawn(self):
        imio.imwrite('lawn.png', self.data)
