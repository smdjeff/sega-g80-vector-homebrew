#!/usr/local/bin/python3

import os,sys,time
import math
import argparse
import struct
import turtle
import canvasvg
from xml.dom import minidom
from svg.path import parse_path
from svg.path.path import Line, CubicBezier


parser = argparse.ArgumentParser(
                    prog='svg2sega',
                    description='Translates SVG to Sega G80 vector symbol',
 formatter_class=argparse.ArgumentDefaultsHelpFormatter
)
parser.add_argument('filename')
parser.add_argument('-s', '--scale', nargs='?', const=1.0, type=float, default=1.0, help='scale image up or down by percentage')
# parser.add_argument('-w', '--write', action='store_true', help='write svg as sega vector symbol')
# parser.add_argument('-d', '--debug', action='store_true', help='print debug information')
args = parser.parse_args()



def calculate_angle_distance(x0, y0, x1, y1):
    distance = math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
    distance *= float(args.scale)
    angle_radians = math.atan2(y1 - y0, x1 - x0)
    angle = math.degrees(angle_radians)
    if angle < 0:
        angle += 360
    return round(distance), round(angle)

def extract_rgb(style):
    if "stroke: rgb" in style:
        color_part = style.split("stroke: rgb(")[1].split(")")[0]
        return tuple(map(int, color_part.split(",")))
    return (255, 255, 255) 


def hex_to_rgb(hex_color):
    hex_color = hex_color.lstrip('#')
    if len(hex_color) == 3:
        hex_color = ''.join(c * 2 for c in hex_color)
    return tuple(int(hex_color[i:i+2], 16) for i in (0, 2, 4))

def rgb_to_2bit(r, g, b):
    r = round(r / 85)
    g = round(g / 85)
    b = round(b / 85)
    return (r<<4) | (g<<2) | b

def polyline_to_path(polyline):
    points = polyline.getAttribute("points").strip()
    if not points:
        return None
    coords = points.split()
    d = "M " + " L ".join(coords)
    return d


def printSegaVector( sega_color, x0, y0, x1, y1 ):
    distance, angle = calculate_angle_distance(x0, y0, x1, y1)
    sega_size = distance
    sega_angle = int(angle * 1024 / 360)
    sega_angle_lsb = sega_angle & 0xFF
    sega_angle_msb = (sega_angle >> 8) & 0xFF
    print("   0x{0:02x}, 0x{1:02x}, 0x{2:02x}, 0x{3:02x},".format(sega_color, sega_size, sega_angle_lsb, sega_angle_msb))


####################################################

print()

doc = minidom.parse( args.filename )
paths = doc.getElementsByTagName("path")
polylines = doc.getElementsByTagName("polyline")

wn = turtle.Screen()
wn.bgcolor("black")
wn.title("Sega Vectors")
wn.colormode(255)
skk = turtle.Turtle()
skk.speed(10)
skk.pensize(2)
skk.pendown()

print('uint8_t sega_vector[] = {')

sz = 0

for element in list(paths) + list(polylines):

    color = (255,255,255)
    if ( element.getAttribute("stroke") ):
        color = hex_to_rgb( element.getAttribute("stroke") )
    else:
        style = element.getAttribute("style")
        color = extract_rgb(style)
    skk.pencolor(color)
    sega_color = rgb_to_2bit(*color) << 1

    if element.tagName == "polyline":
        d = polyline_to_path(element)
    else:
        d = element.getAttribute("d")

    if not d:
        continue  # Skip empty paths

    parsed_path = parse_path(d)

    x3, y3 = 0, 0
    for segment in parsed_path:
        if isinstance(segment, CubicBezier):
            segment = Line(segment.start, segment.end)

        if isinstance(segment, Line):
            x0, y0 = segment.start.real, segment.start.imag
            x1, y1 = segment.end.real, segment.end.imag

            if x0 != x3 or y0 != y3:
                skk.teleport(x0, y0)
                sz += 1
                printSegaVector( sega_color, x3, y3, x0, y0 )

            skk.goto(x0, y0)
            skk.goto(x1, y1)
            sz += 1
            printSegaVector( sega_color|0x01, x0, y0, x1, y1 )

            x3, y3 = x1, y1

print("   0x80, 0x00, 0x00, 0x00" )
print('};')
print('uint16_t sega_vector_sz =', sz, ';')


doc.unlink()

skk.hideturtle()

wn.mainloop()




