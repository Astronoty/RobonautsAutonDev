import math

class Trap:
  acc_perc = 0.02
  dec_perc = 0.02
  dt = 0.02
  acc = 0.0
  max_acc = 0.0
  vel = 0.0
  pos = 0.0
  max_vel = 0.0
  avg_vel = 0.0
  time_1 = time_2 = targ_time = run_time = 0.0
  targ_pos = 0.0
  init_pos = 0.0
  adjust = 0.0

  def __init__(self):
    return
  
  def setPercentAcc(self, accel, decel):
    self.acc_perc = accel
    self.dec_perc = decel
  
  def initialize(self, end, vel, start):
    self.targ_pos = end
    self.init_pos = start
    self.avg_vel = math.fabs(vel)
    if self.avg_vel != 0.0 and self.dt > 0.0:
      self.targ_time = math.fabs((end - start) / self.avg_vel)
      self.time_1 = math.fabs(self.acc_perc * self.targ_time)
      self.time_2 = math.fabs((1 - self.dec_perc) * self.targ_time)
      self.acc = 0.0
      self.vel = 0.0
      self.pos = start
      self.run_time = 0.0
      self.max_vel = (end - start) / (0.5 * self.targ_time * (self.acc_perc + self.dec_perc + 2.0 * (1 - self.acc_perc - self.dec_perc)))
      i = 0
      while i < 0.5 + self.targ_time / self.dt:
        self.vel = self.calcVel(self.run_time, self.max_vel, self.time_1, self.time_2, self.targ_time)
        self.pos += self.dt * self.vel
        self.run_time += self.dt
        i += 1
      self.adjust = self.targ_pos / self.pos
      self.vel = 0.0
      self.acc = 0.0
      self.pos = start
      self.run_time = 0.0
  
  def calcVel(self, time_in, max_vel, time_1, time_2, end_time):
    vel = 0.0
    if time_in < time_1:
      vel = time_in * max_vel / time_1
    elif time_in < time_2:
      vel = max_vel
    elif time_in <= end_time:
      vel = max_vel - (time_in - time_2) * max_vel / (end_time - time_2)
    else:
      vel = 0.0
    return vel

  def update(self):
    vel_prior = self.vel
    self.vel = self.calcVel(self.run_time, self.max_vel, self.time_1, self.time_2, self.targ_time)
    self.pos += self.dt * self.vel
    self.acc = (self.vel - vel_prior) / self.dt
    self.run_time += self.dt

  def getPos(self):
    return self.pos * self.adjust

  def getVel(self):
    return self.vel
  
  def getAcc(self):
    return self.acc

  def getTargTime(self):
    return self.targ_time