import cv2
from kafka import KafkaProducer
import config
import time
import os

def gstreamer_pipeline(
    capture_width=1280,
    capture_height=720,
    display_width=1280,
    display_height=720,
    framerate=20,  # Set framerate to 20 fps
    flip_method=0,
):
    return (
        "nvarguscamerasrc ! "
        "video/x-raw(memory:NVMM), "
        "width=(int)%d, height=(int)%d, "
        "format=(string)NV12, framerate=(fraction)%d/1 ! "
        "nvvidconv flip-method=%d ! "
        "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
        "videoconvert ! "
        "video/x-raw, format=(string)BGR ! appsink"
        % (
            capture_width,
            capture_height,
            framerate,
            flip_method,
            display_width,
            display_height,
        )
    )

topic_name = "send_image"
p = KafkaProducer(
    bootstrap_servers=[config.kafka_ip],
    max_request_size = 9000000,
)
cam = cv2.VideoCapture(gstreamer_pipeline(flip_method=0), cv2.CAP_GSTREAMER)
start_time = time.time()
duration = 10  # capture duration in seconds

while True:
    ret, frame = cam.read()

    # Display the frame (optional)
    cv2.imshow('CSI Camera', frame)

    # Check if the duration has passed
    if time.time() - start_time > duration:
        frame = cv2.resize (frame, dsize=None, fx=0.2, fy=0.2)
        ret, buffer = cv2.imencode('.jpg', frame)
        p.send(topic_name, buffer.tobytes())
        p.flush()
        print("Sent!")
        start_time = time.time()

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break