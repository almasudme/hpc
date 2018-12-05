from celery import Celery
from billiard import current_process
import numpy as np
import librosa
import os
import logging
import time
app = Celery('tasks', broker='amqp://localhost')

# log_location = "D:\\scratch\\fun\\dina\CS626\\project\\"
# if not(os.path.exists(log_location)):
#     create_dirs([log_location])
# main_logger = logging.getLogger(__name__)
# main_formatter = logging.Formatter('%(message)s')
# fh = logging.FileHandler(f"{log_location}/main_logger.log", mode="a")
# os.chmod(f"{log_location}/main_logger.log", 0o777)
# fh.setFormatter(main_formatter)
# main_logger.addHandler(fh)

@app.task
def add(x, y):
    return x + y

@app.task
def parser(file_name,class_name,start):
    # function to load files and extract features
    # file_name = os.path.join('train/Train', str(row.ID) + '.wav')

    # handle exception to check if there isn't a file which is corrupted
    try:
        # here kaiser_fast is a technique used for faster extraction
        X, sample_rate = librosa.load(file_name, res_type='kaiser_fast') 
        # we extract mfcc feature from data
        mfccs = np.mean(librosa.feature.mfcc(y=X, sr=sample_rate, n_mfcc=40).T,axis=0) 
    except Exception as e:
        print("Error encountered while parsing file: ", file_name)
        # logger.info("Error encountered while parsing file: ", file_name)
        return None, None
 
    feature = mfccs
    duration = time.time()-start
    line_array = np.append(feature,class_name+"\n")
    line = ",".join(line_array)

    with open(os.path.join('csv_data',str(current_process().index)+'.csv'),'a') as f1:
        f1.write(line)

    return 