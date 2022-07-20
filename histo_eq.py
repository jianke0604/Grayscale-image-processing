import numpy as np
import cv2
import argparse

parser = argparse.ArgumentParser(description='equalization')
parser.add_argument('--file_path', default='pic/1_in.png', type=str,
                     help='path to the input file')

args = parser.parse_args()

file_in = args.file_path
file_out = "ans.png"

src = cv2.imread(file_in, cv2.IMREAD_GRAYSCALE)[:,:]
dst = cv2.equalizeHist(src)

cv2.imwrite(file_out, dst)
