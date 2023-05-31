import os

import ffmpeg
# 1. Install ffmpeg on your system
# sudo apt install ffmpeg

# 2. Install python binding
# install https://github.com/kkroening/ffmpeg-python

cur_dir = os.getcwd()

ffmpeg\
    .input(f'{cur_dir}/path_to_images/*.JPG', pattern_type='glob', framerate=60)\
    .output('plantTimelapseOct2022.mp4')\
    .run()
