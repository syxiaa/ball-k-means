# This version is completed by Yong Zheng(413511280@qq.com), Shuyin Xia（380835019@qq.com）, Xingxin Chen, Junkuan Wang.  2020.5.1

import ctypes
import numpy as np


class ball_k_means:
    def __init__(self, isRing=True, detail = False):
        self.isRing = isRing
        self.detail = detail

    def fit(self, dataset, centroids):
        # isRing == 0 represent alg with rings
        # isRing == others represent alg with no rings
        temp = np.loadtxt(dataset, dtype=np.int, delimiter=',')
        lenth = temp.shape[0]
        labels = np.linspace(1, lenth, lenth, dtype=int)
        dataptr = labels.ctypes.data_as(ctypes.c_char_p)

        if self.isRing == True:
            print("ball-k-means with dividing ring:")
            dll = ctypes.cdll.LoadLibrary('.\\RingXf.dll')
            dataptr = labels.ctypes.data_as(ctypes.c_char_p)
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_bool)
            dll.ball_kmeans(dataset.encode('utf-8'), centroids.encode('utf-8'), dataptr, lenth, self.detail)
        else:
            print("ball-k-means without dividing ring:")
            dll = ctypes.cdll.LoadLibrary('.\\noRingXf.dll')
            dataptr = labels.ctypes.data_as(ctypes.c_char_p)
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_bool)
            dll.ball_kmeans(dataset.encode('utf-8'), centroids.encode('utf-8'), dataptr, lenth, self.detail)
        return labels


if __name__ == '__main__':
    dataset_address = "c:\\users\\yog\\source\\repos\\test20\\test20\\data+centers\\dataset\\birchdata.csv"
    centriod_address = "c:\\users\\yog\\source\\repos\\test20\\test20\\data+centers\\centroids\\birch4.csv"
    clf = ball_k_means(isRing = True, detail = True)
    labels = clf.fit(dataset_address, centriod_address)
    print(labels)
    # print(m)
