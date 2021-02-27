from random import random
from lawn import Lawn
import numpy as np
import scipy.ndimage as ndi


def generate_random_lawn(width, height):
    shapeWidth = width // 100
    shapeHeight = height // 100
    shape = np.zeros((shapeHeight, shapeWidth), np.uint8)
    shape[shapeHeight // 2][shapeWidth // 2] = 255
    stack = [[shapeWidth // 2 + 1, shapeHeight // 2], [shapeWidth // 2 - 1, shapeHeight // 2],
             [shapeWidth // 2, shapeHeight // 2 + 1], [shapeWidth // 2, shapeHeight // 2 - 1]]
    count = 0

    while len(stack) > count:
        cell = stack[count]
        x = cell[0]
        y = cell[1]

        if count < 20 or random() > 0.55:
            shape[y][x] = 255
            if x + 1 < shapeWidth and shape[y][x + 1] != 255:
                stack.append([x + 1, y])

            if x - 1 >= 0 and shape[y][x - 1] != 255:
                stack.append([x - 1, y])

            if y + 1 < shapeHeight and shape[y + 1][x] != 255:
                stack.append([x, y + 1])

            if y - 1 >= 0 and shape[y - 1][x] != 255:
                stack.append([x, y - 1])
        else:
            shape[y][x] = 1

        count += 1

    for i in range(1, shapeHeight - 1):
        for j in range(1, shapeWidth - 1):
            if (shape[i][j - 1] == 255 and shape[i][j + 1] == 255) or (shape[i - 1][j] == 255 and shape[i + 1][j] == 255):
                shape[i][j] = 255

    for i in range(shapeHeight):
        for j in range(shapeWidth):
            if shape[i][j] == 1:
                shape[i][j] = 0

    lawn = Lawn(width, height)
    lawn.data = ndi.zoom(shape, 100, order=0)
    return lawn


_lawn = generate_random_lawn(8000, 4000)
_lawn.print_lawn()
_lawn.draw_lawn()
