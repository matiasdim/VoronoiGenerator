#! /usr/bin/python

from PIL import Image
import random
import argparse

parser = argparse.ArgumentParser(description='Voronoi image generator')
parser.add_argument('file', help='Matrix file')
parser.add_argument('seeds', type=int, help='Number of seeds')
parser.add_argument('width', type=int, help='width of the image')
parser.add_argument('height', type=int, help='Height of the image')


def main():
    args = parser.parse_args();

    img = Image.new('RGB', (args.width, args.height), 'black')

    pixels = img.load()
    colors = []
    for i in range(args.seeds):
        colors.append(
            (random.randint(0,255), random.randint(0,255), random.randint(0,255)))
    colors.append((255, 255, 255))

    with open('test') as file:
        for i, line in enumerate(file):
            line = line.strip().split(' ')
            for j, k in enumerate(line):
                pixels[i, j] =  colors[int(k)]
            i = i + 1

    img.show()

if __name__ == '__main__':
    main()
