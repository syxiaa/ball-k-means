# Python version:

* the param "isRing" is used to switch ring version and no ring version of the algorithm.

* According to our experience, the "Xd" version can get more accurate results but the running time is slightly slower, and the "Xf" version can reach the fastest running time, but low accuracy will result in inaccurate results.

# Requirements

### Installation requirements (Python):

* Only need to rely on the .dll(win)/.so(linux) files in the "PythonVersion" file.

# Using

## python version:

### Step 1: declare class "ball_k_means" and initialize algorithm.

#### Parameters: 

* isDouble: bool type, calculation accuracy, true:double false:float


### Step 2: call "fit" function

#### Parameters: 

* dataset: absolute path of th csv file of clustering data.

* s1: Absolute path of dataset

* s2: Absolute path of initial center point

* k： K value of random initial point

* isRing： boll type, switch the ring version and the no ring version of the algorithm. "true" means the current algorithm is a ring version, and "true" means the current algorithm is no ring version. The default is false.

* detail: bool type, "true" means output detailed information (including k value, distance calculation times, time, etc.), "false" means no detailed information is output. The default is false.

* random_seed: Kmeans + + random number seed

#### Output: 

* labels: labels of clustering data in numpy matrix format.
