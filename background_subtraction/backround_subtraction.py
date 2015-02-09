import sys
import cv2
import numpy as np
import time

FPS = 30

cam = cv2.VideoCapture(0)
cam.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, 640)
cam.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, 480)
_, f = cam.read()

last_update = time.time()
avg = np.float32(f)

# loop over images and estimate background 
while True:
    #print time.time() - last_update
    if time.time() - last_update < 1.0/FPS:
        continue

    print ".",
    sys.stdout.flush()

    _,f = cam.read()

    cv2.accumulateWeighted(f,avg,0.1)
    res = cv2.convertScaleAbs(f-avg)

    cv2.imshow('avg',res)

    last_update = time.time()

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
cam.release()
cv2.destroyAllWindows()

