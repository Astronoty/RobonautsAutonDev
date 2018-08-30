import xml.etree.ElementTree as ET
import math

tree = None
root = None

waypoints = [[], []]
thetas = []

def readFile(filename, stepname):
  global tree, root, waypoints, thetas
  tree = ET.parse(filename)
  root = tree.getroot()

  for elem in root:
    if elem.attrib.get('name') == stepname:
      for subelem in elem:
        if 'x' in subelem.keys():
          print(subelem.attrib.get('x'), subelem.attrib.get('y'), subelem.attrib.get('theta'))
          waypoints[0].append(float(subelem.attrib.get('x')))
          waypoints[1].append(float(subelem.attrib.get('y')))
          thetas.append(float(subelem.attrib.get('theta')))
    else:
      continue

def getBezierVars():
  return waypoints, thetas