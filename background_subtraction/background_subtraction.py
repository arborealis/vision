import sys
import cv2
import numpy as np
import time

FPS = 30
WIDTH, HEIGHT = 640, 480

if __name__ == "__main__":
    cam = cv2.VideoCapture(0)
    cam.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, WIDTH)
    cam.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, HEIGHT)

    try:
        start_time = time.time()
        last_update = time.time()
        _, f = cam.read()
        avg = np.float32(f)

        # loop over images and estimate background 
        count = 0
        while True:
            #print time.time() - last_update
            #if time.time() - last_update < 1.0/FPS:
            #    continue

            _,f = cam.read()

            cv2.accumulateWeighted(f,avg,0.1)
            res = cv2.convertScaleAbs(f-avg)

            cv2.imshow('avg',res)

            last_update = time.time()
            count += 1

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    except KeyboardInterrupt:
        print "Actual fps: %.1f" % (float(count / (time.time() - start_time)))

    cam.release()
    cv2.destroyAllWindows()

