from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from flask import Flask
from flask import render_template , request
from flask_cors import CORS, cross_origin
import tensorflow as tf
import argparse
import facenet
import os
import sys
import math
import pickle
import align.detect_face
import numpy as np
import cv2
import collections
from sklearn.svm import SVC

import json
from datetime import datetime
import paho.mqtt.client as mqtt

from PIL import Image

from kafka import KafkaConsumer, KafkaProducer

# Kafka config
sub_topic = "send_image"
pub_topic = "receive_result"

c = KafkaConsumer(
    sub_topic,
    bootstrap_servers = ["192.168.0.82:9092"],
    auto_offset_reset = 'latest',
    enable_auto_commit = True,
    fetch_max_bytes = 9000000,
    fetch_max_wait_ms = 10000,
)

p = KafkaProducer(
    bootstrap_servers=["192.168.0.82:9092"],
    max_request_size = 9000000,
)

# MQTT config
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe('v1/devices/me/telemetry')

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.payload))

THINGSBOARD_HOST = 'mqtt.thingsboard.cloud'
ACCESS_TOKEN = 'Q24KljOeksGaq2fgUipo'

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set(ACCESS_TOKEN)

client.connect(THINGSBOARD_HOST, 1883, 60)

# CV Parameters
MINSIZE = 20
THRESHOLD = [0.6, 0.7, 0.7]
FACTOR = 0.709
IMAGE_SIZE = 182
INPUT_IMAGE_SIZE = 160
CLASSIFIER_PATH = '../Models/facemodel.pkl'
FACENET_MODEL_PATH = '../Models/20180402-114759.pb'

# Load The Custom Classifier
with open(CLASSIFIER_PATH, 'rb') as file:
    model, class_names = pickle.load(file)
print("Custom Classifier, Successfully loaded")

with tf.Graph().as_default():

    # Cai dat GPU neu co
    gpu_options = tf.compat.v1.GPUOptions(per_process_gpu_memory_fraction=0.6)
    sess = tf.compat.v1.Session(config=tf.compat.v1.ConfigProto(gpu_options=gpu_options, log_device_placement=False))

    with sess.as_default():
        # Load the model
        print('Loading feature extraction model')
        facenet.load_model(FACENET_MODEL_PATH)

        images_placeholder = tf.compat.v1.get_default_graph().get_tensor_by_name("input:0")
        embeddings = tf.compat.v1.get_default_graph().get_tensor_by_name("embeddings:0")
        phase_train_placeholder = tf.compat.v1.get_default_graph().get_tensor_by_name("phase_train:0")
        embedding_size = embeddings.get_shape()[1]

        pnet, rnet, onet = align.detect_face.create_mtcnn(sess, "align")


def model_inference(frame):
        name = "Unknown"
        bounding_boxes, _ = align.detect_face.detect_face(frame, MINSIZE, pnet, rnet, onet, THRESHOLD, FACTOR)

        faces_found = bounding_boxes.shape[0]

        if faces_found > 0:
            det = bounding_boxes[:, 0:4]
            bb = np.zeros((faces_found, 4), dtype=np.int32)
            for i in range(faces_found):
                bb[i][0] = np.maximum(det[i][0]-32/2, 0)
                bb[i][1] = np.maximum(det[i][1]-32/2, 0)
                bb[i][2] = np.maximum(det[i][2]+32/2, 160)
                bb[i][3] = np.maximum(det[i][3]+32/2, 160)
                cropped = frame[bb[i][1]:bb[i][3], bb[i][0]:bb[i][2], :]
                scaled = cv2.resize(cropped, (160, 160),
                                    interpolation=Image.BILINEAR)
                scaled = facenet.prewhiten(scaled)
                scaled_reshape = scaled.reshape(-1, 160, 160, 3)
                feed_dict = {images_placeholder: scaled_reshape, phase_train_placeholder: False}
                emb_array = sess.run(embeddings, feed_dict=feed_dict)
                predictions = model.predict_proba(emb_array)
                best_class_indices = np.argmax(predictions, axis=1)
                best_class_probabilities = predictions[
                    np.arange(len(best_class_indices)), best_class_indices]
                best_name = class_names[best_class_indices[0]]
                print("Name: {}, Probability: {}".format(best_name, best_class_probabilities))

                if best_class_probabilities > 0.6:
                    name = best_name
                    break
                else:
                    name = "Unknown"

        return name

for message in c:
    stream = message.value
    stream = np.frombuffer(stream, dtype=np.uint8)
    image = cv2.imdecode(stream, cv2.IMREAD_COLOR)
    print("Recognizing...")
    prediction = model_inference(image)
    now = datetime.now()
    formatted_time = now.strftime("%H:%M:%S %d/%m/%Y")
    json_msg = json.dumps({"Timestamp":formatted_time,"RoomID":"E3.100","StudentName":prediction}) 
    p.send(pub_topic, json_msg.encode("utf-8"))
    client.publish('v1/devices/me/telemetry', json_msg, 1)
    print("Message published: ", json_msg)
    p.flush()





