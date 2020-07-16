# This version is completed by Yong Zheng(413511280@qq.com), Shuyin Xia（380835019@qq.com）, Xingxin Chen, Junkuan Wang.  2020.5.1

import ctypes
class ball_k_means:
    def __init__(self, isRing = 0):
        self.isRing = isRing

    def fit(self, s1, s2):
        # isRing == 0 represent alg with rings
        # isRing == others represent alg with no rings
        if self.isRing == 0:
            print("have ring: ")
            dll = ctypes.cdll.LoadLibrary('.\\RingXd.dll')
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p)
            dll.ball_kmeans(s1.encode('utf-8'), s2.encode('utf-8'))
        else:
            print("have no ring: ")
            dll = ctypes.cdll.LoadLibrary('.\\noRingXd.dll')
            dll.ball_kmeans.argtypes = (ctypes.c_char_p, ctypes.c_char_p)
            dll.ball_kmeans(s1.encode('utf-8'), s2.encode('utf-8'))

if __name__ == '__main__':
    dataset_address = "c:\\users\\yog\\source\\repos\\test20\\test20\\data+centers\\dataset\\birchdata.csv"
    centriod_address = "c:\\users\\yog\\source\\repos\\test20\\test20\\data+centers\\centroids\\birch5.csv"
    clf = ball_k_means(isRing=0)
    clf.fit(dataset_address, centriod_address)
