#! /usr/bin/python

import sys
import argparse

parser = argparse.ArgumentParser(description="Test matrix generator")
parser.add_argument('rows', type=int, help='Rows of the matrix')
parser.add_argument('cols', type=int, help='Cols of the matrix')


def main():
    args = parser.parse_args()
    rows = args.rows
    cols = args.cols

    for i in range(rows):
        for j in range(cols):
            if i <= rows/2 and j <= cols/2:
                k = 0
            elif i > rows/2 and j < cols/2:
                k = 1
            elif i <= rows/2 and j > cols/2:
                k = 2
            elif i > rows/2 and j >= cols/2:
                k = 3
            sys.stdout.write("%d " % k)
        sys.stdout.write("\n")


if __name__ == '__main__':
    main()
