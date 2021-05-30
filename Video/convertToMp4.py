import os
print('Please input filename: ')

avi_file_path = os.path.dirname(os.path.realpath(__file__)) + '/' + str(input())
output_name = 'output.mp4'
os.popen("ffmpeg -i '{input}' -ac 2 -b:v 2000k -c:a aac -c:v libx264 -b:a 160k -vprofile high -bf 0 -strict experimental -f mp4 '{output}.mp4'".format(input = avi_file_path, output = output_name))
