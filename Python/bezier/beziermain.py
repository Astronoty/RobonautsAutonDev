import bezier as bz
import bezierspline as bzs
import xml_reader as xml

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import sys, getopt
import pymsgbox

waypoints = [[], []]
theta = []
points = []
z = []

filename = ''
stepname = ''

try:
  opts, args = getopt.getopt(sys.argv[1:], 'hf:n:', ['help', 'file', 'step-name'])
except getopt.GetoptError:
  print('beziermain.py [-f <input_csv> -n <step_name>]')
  sys.exit(2)
for opt, arg, in opts:
  if opt in ('-h', '--help'):
    print('beziermain.py [-f <input_csv> -n <step_name>]')
    sys.exit()
  elif opt in ('-f', '--file'):
    filename = arg
  elif opt in ('-n', '--step-name'):
    stepname = arg

if filename == '':
  filename = pymsgbox.prompt('Enter the XML filename.')
if stepname == '':
  stepname = pymsgbox.prompt('Enter the step name to plot.')

xml.readFile(filename, stepname)

waypoints, theta = xml.getBezierVars()

spline = bzs.BezierSpline(waypoints, theta)

i = 0.0
while i < len(waypoints[0]) - 1:
  point = spline.calculateSplinePoint(i)
  # print(i, point)
  points.append(point)
  z.append(i)
  i += 0.005

cmap = sns.cubehelix_palette(start=2.4, rot=0.1, n_colors=6, dark=0.3, as_cmap=True)
plt.figure(num='Bezier Spline')
x = [p[0] for p in points]
y = [p[1] for p in points]
plt.scatter(x, y, c=z, cmap=cmap)
plt.scatter(waypoints[0], waypoints[1], c='black')
plt.xlabel('X Position')
plt.ylabel('Y Position')
plt.title('Bezier Spline')
plt.show()