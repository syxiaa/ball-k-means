# This version is completed by Yong Zheng(413511280@qq.com), Shuyin Xia（380835019@qq.com）, Xingxin Chen, Junkuan Wang.  2020.5.1

import ctypes
import numpy as np


class ball_k_means:
    def __init__(self, isRing=0):
        self.isRing = isRing

    def fit(self, s1, s2, detail):
        # isRing == 0 represent alg with rings
        # isRing == others represent alg with no rings
        temp = np.loadtxt(s1, dtype=np.int, delimiter=',')
        lenth = temp.shape[0]
        m = np.linspace(1, lenth, lenth, dtype=int)
        dataptr = m.ctypes.data_as(ctypes.c_char_p)

        if self.isRing == 1:
            print("have ring: ")
            dll = ctypes.cdll.LoadLibrary('.\\RingXd.dll')
            dataptr = m.ctypes.data_as(ctypes.c_char_p)
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_bool)
            dll.ball_kmeans(s1.encode('utf-8'), s2.encode('utf-8'), dataptr, lenth, detail)
        else:
            print("have no ring: ")
            dll = ctypes.cdll.LoadLibrary('.\\noRingXd.dll')
            dataptr = m.ctypes.data_as(ctypes.c_char_p)
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_bool)
            dll.ball_kmeans(s1.encode('utf-8'), s2.encode('utf-8'), dataptr, lenth, detail)
        return m


if __name__ == '__main__':
    dataset_address = "C:\\Users\\wjk\\OneDrive - atuo\\Work\\python_work\\ball_kmeans\\data+centers\\dataset\\birchdata.csv"
    centriod_address = "C:\\Users\\wjk\\OneDrive - atuo\\Work\\python_work\\ball_kmeans\\data+centers\\centroids\\birch4.csv"
    detail = True
    clf = ball_k_means(isRing=0)
    m = clf.fit(dataset_address, centriod_address, detail)
    # print(m)
