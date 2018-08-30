import xml_reader as xml
import segment as seg
import matplotlib.pyplot as plt
import seaborn as sns
import sys, getopt
import pymsgbox

filename = ''
stepname = ''

try:
  opts, args = getopt.getopt(sys.argv[1:], 'hf:n:', ['help', 'file', 'step-name'])
except getopt.GetoptError:
  print('pathgen.py [-f <input_csv> -n <step_name>]')
  sys.exit(2)
for opt, arg, in opts:
  if opt in ('-h', '--help'):
    print('pathgen.py [-f <input_csv> -n <step_name>]')
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

init_head, final_head, perc_switch, tot_dist, speed, acc_perc, dec_perc = xml.getSegmentVars()

seg.setSegVecs(init_head, final_head, perc_switch)
seg.driveSegment(tot_dist, speed, acc_perc, dec_perc)

dt = 0.02
x, y, z = seg.getPoses(dt)
cmap = sns.cubehelix_palette(start=2.4, rot=0.1, n_colors=4, dark=0.3, as_cmap=True)
plt.figure(num='Segment Path')
plt.scatter(x, y, c=z, cmap=cmap)
plt.xlabel('X Position')
plt.ylabel('Y Position')
plt.title('Segment Path')
plt.show()