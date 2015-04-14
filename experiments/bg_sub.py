import numpy as np
import cv2

cam = cv2.VideoCapture(0)
cam.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, 1280)
cam.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, 720)

kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
fgbg = cv2.BackgroundSubtractorMOG2()

while(1):
    ret, frame = cam.read()

    fgmask = fgbg.apply(frame)
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel)

    cv2.imshow('frame', fgmask)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cam.release()
cv2.destroyAllWindows()
