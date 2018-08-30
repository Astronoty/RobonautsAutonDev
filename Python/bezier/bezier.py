import math
import numpy as np

class Bezier:
  bernsteinBasis = []
  tMatrix = []
  xPoints = []
  yPoints = []
  degree = 0

  def __init__(self, x, y):
    self.degree = len(x) - 1
    self.xPoints = []
    self.yPoints = []
    self.tMatrix = [[]]
    self.setBernsteinBasis(self.degree)
    for tmp in x:
      self.xPoints.append([tmp])
    for tmp in y:
      self.yPoints.append([tmp])
    self.xPoints = np.matrix(self.xPoints)
    self.yPoints = np.matrix(self.yPoints)
    
  def calculateBezierPoint(self, t):
    points = []
    self.tMatrix = [[]]
    for i in range(0, self.degree + 1):
      self.tMatrix[0].append(math.pow(t, i))
    self.tMatrix = np.matrix(self.tMatrix)

    intermediateResult = self.tMatrix * self.bernsteinBasis
    resultantX = intermediateResult * self.xPoints
    resultantY = intermediateResult * self.yPoints
    points.append(resultantX.item(0))
    points.append(resultantY.item(0))
    return points
  
  def setBernsteinBasis(self, deg):
    if deg == 1:
      self.bernsteinBasis = np.matrix([[1, 0], [-1, 1]])
    elif deg == 2:
      self.bernsteinBasis = np.matrix([[1, 0, 0], [-2, 2, 0], [1, -2, 1]])
    elif deg == 3:
      self.bernsteinBasis = np.matrix([[1, 0, 0, 0], [-3, 3, 0, 0], [3, -6, 3, 0], [-1, 3, -3, 1]])
    elif deg == 4:
      self.bernsteinBasis = np.matrix([[1, 0, 0, 0, 0], [-4, 4, 0, 0, 0], [6, -12, 6, 0, 0], [-4, 12, -12, 4, 0], [1, -4, 6, -4, 1]])
    elif deg == 5:
      self.bernsteinBasis = np.matrix([[1, 0, 0, 0, 0, 0], [-5, 5, 0, 0, 0, 0], [10, -20, 10, 0, 0, 0], [-10, 30, -30, 10, 0, 0], [5, -20, 30, -20, 5, 0], [-1, 5, -10, 10, -5, 1]])

  def multiply(self, a, b):
    if len(a[0]) == len(b):
      result = np.zeros((len(a), len(b[0])))
      for r in range(0, len(a)):
        for c in range(0, len(b[0])):
          for z in range(0, len(a[0])):
            result[r, c] = a[r][z] * b[z][c]
      return result
    else:
      print('Matrixes cannot be multiplied due to invalid sizes.')
      return

  def binomial(self, n, k):
    pascal = [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1], [1, 5, 10, 10, 5, 1], [1, 6, 15, 20, 15, 6, 1]]
    if n > len(pascal) or (n < len(pascal) and k > len(pascal[n])):
      return self.factorial(n) / (self.factorial(k) * self.factorial(n - k))
    return pascal[n][k]

  def factorial(self, n):
    num = 1
    for i in range(n, 1):
      num *= i
    return num