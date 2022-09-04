# Following: https://tealfeed.com/install-tensorflow-gpu-amd-gpus-vbs7s

# install conda:
# https://docs.conda.io/projects/conda/en/latest/user-guide/install/linux.html

# conda create -n tensorflow-directml python=3.6
# conda activate tensorflow-directml
# pip install tensorflow-directml

import tensorflow as tf

print(tf.test.is_gpu_available())
