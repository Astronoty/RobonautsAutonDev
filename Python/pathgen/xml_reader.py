import xml.etree.ElementTree as ET
import math

tree = None
root = None
init_head = []
final_head = []
perc_switch = []
tot_dist = 0.0
speed = 0.0
acc_perc = 0.0
dec_perc = 0.0

def readFile(filename, stepname):
  global tree, root, init_head, final_head, perc_switch, tot_dist, speed, acc_perc, dec_perc
  tree = ET.parse(filename)
  root = tree.getroot()

  for elem in root:
    if elem.attrib.get('name') == stepname:
      speed = float(elem.attrib.get('speed'))
      acc_perc = float(elem.attrib.get('accel_percent'))
      dec_perc = float(elem.attrib.get('decel_percent'))

      for subelem in elem:
        if 'distance' in subelem.keys():
          tot_dist += float(subelem.attrib.get('distance'))

      perc_switch_cum = 0.0
      for subelem in elem:
        if 'distance' in subelem.keys():
          perc_switch_cum += float(subelem.attrib.get('distance')) / tot_dist
          perc_switch.append(math.fabs(perc_switch_cum))
          init_head.append(float(subelem.attrib.get('init_heading')))
          final_head.append(float(subelem.attrib.get('final_heading')))
    else:
      continue

def getSegmentVars():
  return init_head, final_head, perc_switch, tot_dist, speed, acc_perc, dec_perc