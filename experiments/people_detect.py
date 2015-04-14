import numpy as np
import cv2


def inside(r, q):
    rx, ry, rw, rh = r
    qx, qy, qw, qh = q
    return rx > qx and ry > qy and rx + rw < qx + qw and ry + rh < qy + qh


def draw_detections(img, rects, thickness=1):
    for x, y, w, h in rects:
        # the HOG detector returns slightly larger rectangles than
        # the real objects. so we slightly shrink the rectangles to get
        # a nicer output.
        pad_w, pad_h = int(0.15*w), int(0.05*h)
        cv2.rectangle(
            img,
            (x+pad_w, y+pad_h),
            (x+w-pad_w, y+h-pad_h),
            (0, 255, 0),
            thickness)


if __name__ == '__main__':
    cam = cv2.VideoCapture(0)
    cam.set(cv2.cv.CV_CAP_PROP_FRAME_WIDTH, 640)
    cam.set(cv2.cv.CV_CAP_PROP_FRAME_HEIGHT, 480)

    hog = cv2.HOGDescriptor()
    hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

    while True:
        ret, frame = cam.read()

        found, w = hog.detectMultiScale(
            frame,
            winStride=(8, 8), padding=(32, 32), scale=1.05)
        found_filtered = []
        for ri, r in enumerate(found):
            for qi, q in enumerate(found):
                if ri != qi and inside(r, q):
                    break
            else:
                found_filtered.append(r)
        draw_detections(frame, found)
        draw_detections(frame, found_filtered, 3)

        cv2.imshow('frame', frame)

        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

    cam.release()
    cv2.destroyAllWindows()
