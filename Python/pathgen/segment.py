import trap
import math

trap = trap.Trap()
init_head = []
final_head = []
perc_switch = []
count = 0
max_count = len(init_head)

x_pos = 0.0
y_pos = 0.0
z_pos = 0.0
x_poses = []
y_poses = []
z_poses = []
head = []
pos_idx = 0
dist = 0.0
dist_des = 0.0
gyro_des = 0.0

def setSegVecs(ihead, fhead, pswitch):
  global init_head, final_head, perc_switch, max_count
  init_head = ihead
  final_head = fhead
  perc_switch = pswitch
  max_count = len(init_head)

def driveSegment(d, v, acc, dec):
  global dist_des
  trap.setPercentAcc(acc, dec)
  trap.initialize(d, v, 0)
  dist_des = d

def updateCartesian(h, d):
  global x_pos, y_pos, x_poses, y_poses, head, pos_idx
  x_pos += d * math.cos(h * math.pi / 180)
  x_poses.append(x_pos)
  y_pos += d * math.sin(h * math.pi / 180)
  y_poses.append(y_pos)
  head.append(h)
  pos_idx += 1

def getPercentSegment():
  global count, z_pos, z_poses
  _init_head = init_head[count]
  _final_head = final_head[count]
  _perc_switch = perc_switch[count]
  ret = 0

  traveled_perc = dist / dist_des
  perc = 0
  if count > 0:
    perc = (traveled_perc - perc_switch[count - 1]) / (_perc_switch - perc_switch[count - 1])
  else:
    perc = traveled_perc / _perc_switch
  z_pos = traveled_perc
  z_poses.append(z_pos)

  if (traveled_perc > _perc_switch or perc >= 1.0) and count < max_count - 1:
    count += 1
    ret = init_head[count]
  else:
    ret = perc * (_final_head - _init_head) + _init_head
  return ret

def doSegmentMode():
  global dist, gyro_des
  dist_prev = dist
  trap.update()
  dist = trap.getPos()
  gyro_des = getPercentSegment()
  updateCartesian(gyro_des, dist - dist_prev)

def getPoses(dt):
  i = 0
  while i < trap.getTargTime():
    doSegmentMode()
    i += dt
  # print('x: {0} y: {1} h: {2}'.format(x_pos, y_pos, head[pos_idx - 1]))
  return x_poses, y_poses, z_poses