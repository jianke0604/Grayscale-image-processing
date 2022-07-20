import math
import cv2
import numpy as np
import argparse

parser = argparse.ArgumentParser(description='picture decoder')
parser.add_argument('--file_path', default='out.png', type=str,
                     help='path to the output file')

args = parser.parse_args()
filename = args.file_path

with open('out.txt', 'r') as f:
    a = f.read().split('\n')
    hw = a[0].split(' ')
    h, w = int(hw[0]), int(hw[1])

    ex = np.zeros((h, w))

    tt = 1
    for i in range(h):
        for j in range(w):
            ex[i][j] = int(a[tt])
            tt += 1

    '''
    Correponding C++ code:

    a = f.read().split('\n')
        like std::vector<std::string>
        each element contains a line of file to read

    np.zeros((h, w))
        create a 2D array filled with 0s

    for i in range(h):
        for j in range(w):
            ex[i][j] = int(a[tt])
            tt += 1

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                ex[i][j] = atoi(a[tt++])  
    '''

cv2.imwrite(filename, ex)


