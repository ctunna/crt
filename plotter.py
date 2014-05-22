import math
import random

radius = 800
z = 600
rstep = math.pi / 14
zstep = 10
pts = []
pt = []
t = 0

for i in range(0, 1000):
    t += rstep
    z += zstep    
    x = radius * math.cos(t) + 100
    y = radius * math.sin(t) + 200
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
#    radius -= zstep
    pt = (x,y,z,r,g,b)
    pts.append(pt)

with open('spheres.obj', 'w') as f:
    for obj in pts:
        f.write('{:.5f}'.format(obj[0]) + ' ' + '{:.5f}'.format(obj[1]) + ' ' + '{:.5f}'.format(obj[2]) + ' ' + str(obj[3]) + ' ' + str(obj[4]) + ' ' + str(obj[5]) + '\n')
    








