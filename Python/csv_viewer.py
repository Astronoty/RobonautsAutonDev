import matplotlib.pyplot as plt
import pandas as pd
import sys, getopt
import pymsgbox

# Initialize input variables
filename = ''
plot_type = ''
title = 'CSV Data'
x_name = ''
y_names = []

# Get as much data as possible from command line arguments
try:
  opts, args = getopt.getopt(sys.argv[1:], 'hf:p:t:x:y:', ['help', 'file', 'plot-type', 'title'])
except getopt.GetoptError:
  print('csv_viewer.py -f <input_csv> [-t <title> -p <plot_type> -x <x_variable> -y <y_variables>]')
  sys.exit(2)
for opt, arg, in opts:
  if opt in ('-h', '--help'):
    print('csv_viewer.py -f <input_csv> [-t <title> -p <plot_type> -x <x_variable> -y <y_variables>]')
    sys.exit()
  elif opt in ('-f', '--file'):
    filename = arg
  elif opt in ('-p', '--plot-type'):
    plot_type = arg
  elif opt in ('-t', '--title'):
    title = arg
  elif opt == '-x':
    x_name = arg
  elif opt == '-y':
    y_names = sys.argv[sys.argv.index(arg):]

# Use message boxes for anything that wasn't given in arguments
if filename == '':
  filename = pymsgbox.prompt('Enter the CSV filename.')
if plot_type == '':
  plot_type = pymsgbox.prompt('Enter the plot type (line or scatter).')
if x_name == '':
  x_name = pymsgbox.prompt('Enter the column to be used on the x-axis.')
if y_names == []:
  y_names = [x.strip() for x in pymsgbox.prompt('Enter the column(s) to be used on the y-axis.').split(',')]

# Read the CSV file and sort by the x variable
df = pd.read_csv(filename).rename(columns=lambda x: x.strip())
df.sort_values(x_name)

# Create a line plot of the selected data
if plot_type == 'line':
  plt.figure(num=title)
  plt.title(title)

  x_data = df[x_name].get_values()
  plt.xlabel(x_name)

  for name in y_names:
    data = df[name].get_values()
    plt.plot(x_data, data, label=name)
  plt.legend(loc='upper right')

# Create a scatter plot of the selected data
elif plot_type == 'scatter':
  x_data = df[x_name].get_values()
  y_data = df[y_names[0]].get_values()
  
  plt.figure(num=title)
  plt.scatter(x_data, y_data)
  plt.title(title)
  plt.xlabel(x_name)
  plt.ylabel(y_names[0])

# Show the plot
plt.show()