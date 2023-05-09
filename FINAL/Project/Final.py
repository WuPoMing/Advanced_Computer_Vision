import numpy as np
import time
import os

def preprocess(file_path):

    with open(file_path, "r", encoding="utf-8") as f:
        data = [line.strip("\n").split(" ") for line in f]

    list = []

    for i, line in enumerate(data):

        if line[0] == "25" and len(data[i-2]) == 1:
            
            for j in range(i+1, i+26):

                list.append(data[j][0:3])

    l2 = [list[i:i+25] for i in range(0, len(list), 25)]

    return np.array(l2).astype(float)

def predict(data_array):
    
    diff = np.diff(data_array, axis=0)

    sum = np.sum(diff, axis=0) # (25, 3)

    sum_abs_xyz = np.sum(np.sum(np.abs(diff), axis=0), axis=1) # (25)
    abs_max_joint = np.argmax(sum_abs_xyz) + 1

    if sum_abs_xyz[3] < 1.21:
        if abs_max_joint == 22 or abs_max_joint == 23 or abs_max_joint == 24 or abs_max_joint == 25:
            print("Hand waving")
        elif abs_max_joint == 15 or abs_max_joint == 16 or abs_max_joint == 19 or abs_max_joint == 20:
            print("Kicking something")
        else:
            print("cannot predict!")
    elif sum[3][1] > 0:
        print("Stand up")
    elif sum[3][1] < 0:
        print("Sit down")
    else:
        print("cannot predict!")

if __name__ == "__main__":

    while(True):

        FILE_PATH = input("Please enter a Skeleton File Path(or 'q' for exit): ")

        if FILE_PATH == 'q':
            break

        elif os.path.exists(FILE_PATH):

            start = time.time()

            dataArray = preprocess(FILE_PATH)
            print('Predict: ',  end='')
            predict(dataArray)

            end = time.time()
            print("Excute time: %f sec." %(end-start))
            print()

        else:
            print("No such file: %s" %(FILE_PATH))
            print()

os.system("pause")