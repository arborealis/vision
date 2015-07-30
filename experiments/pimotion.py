import picamera
import picamera.array
import numpy as np
import cv2
import time

class MotionAnalyser(picamera.array.PiMotionAnalysis):
    def __init__(self, camera, size=None):
        super(MotionAnalyser, self).__init__(camera, size)
        self.cols = None
        self.rows = None
        self.num_frames = 0

    def analyse(self, a):
        self.num_frames += 1
        # Calculate the motion vector polar lengths
        r = np.sqrt(
            np.square(a['x'].astype(np.float)) +
            np.square(a['y'].astype(np.float))
            ).clip(0, 255).astype(np.uint8)

        # Calculate the motion vector polar angles
        # arctan values are + or - pi (radians)
        # OpenCV hue values are 0-179 (degrees)
        phi = ((np.arctan2(
              a['y'].astype(np.float),
              a['x'].astype(np.float)) +
              np.pi) * 180/(2*np.pi)
              ).clip(0, 179).astype(np.uint8)

        # Make an array for a fixed colour saturation
        sat = np.empty_like(r)
        sat[:] = 255 # 100% saturation

        # Assemble the HSV image array
        hsv = cv2.merge((phi,sat,r))

        # Change to the native OpenCV array (BGR)
        bgr = cv2.cvtColor(hsv,cv2.COLOR_HSV2BGR)

        # Expand the image - 16x zoom
        big=cv2.resize(bgr,None,fx=16,fy=16)
        # Show the image in the window
        cv2.imshow( 'PiMotionAnalysis', big )
        key = cv2.waitKey(100)

with picamera.PiCamera() as camera:
    camera.resolution = (640, 480)
    with MotionAnalyser(camera) as output:
        cv2.namedWindow( 'PiMotionAnalysis' )

        start_time = time.clock()
        camera.start_recording('/dev/null', 'h264', motion_output=output)
        camera.wait_recording(20) # continue recording for 20 seconds
        camera.stop_recording()
        end_time = time.clock()
        print "FPS: {}".format(output.num_frames / (end_time-start_time))

        cv2.destroyWindow('PiMotionAnalysis')
