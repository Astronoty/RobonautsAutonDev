import bezier as bz
import math

class BezierSpline:
  waypoints = []
  headings = []
  slopes = []
  piecewiseBeziers = []

  def __init__(self, way, head):
    self.waypoints = way
    self.headings = head
    self.convertHeadingToSlope()
    self.generateCubicBezier()

  def generateCubicBezier(self):
    for i in range(0, len(self.waypoints[0]) - 1):
      self.piecewiseBeziers.append(self.createCubicBezierSegment(self.waypoints[0][i], self.waypoints[1][i], self.waypoints[0][i+1], self.waypoints[1][i+1], self.slopes[i], self.slopes[i+1]))

  def calculateSplinePoint(self, t):
    point = self.piecewiseBeziers[int(t)].calculateBezierPoint(t - float(int(t)))
    return point

  def convertHeadingToSlope(self):
    ZERO = 0.00000001
    for i in range(0, len(self.headings)):
      if self.headings[i] == 0.0:
        self.slopes.append(ZERO)
      elif self.headings[i] == 180.0:
        self.slopes.append(ZERO)
      else:
        self.slopes.append(1 / math.tan(self.headings[i] * math.pi / 180.0))

  def createCubicBezierSegment(self, startX, startY, endX, endY, ts, te):
    # print('STARTX', startX)
    # print('TS', ts)
    # print('TE', te)
    # print('ENDX', endX)

    x = [startX, (1.0/3.0)*(endX - startX) + startX, endX - (1.0/3.0)*(endX - startX), endX]
    y = [startY, (1.0/3.0)*te + startY, endY - (1.0/3.0)*ts, endY]

    # print('P0', x[0], 'P1', x[1], 'P2', x[2], 'P3', x[3])
    # print('P0', y[0], 'P1', y[1], 'P2', y[2], 'P3', y[3])

    bez = bz.Bezier(x, y)
    return bez