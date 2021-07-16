from moviepy.editor import *
from PIL import Image

def crop_image_16_to_9(filename):
    """Always takes the upper 16:9 part of the picture. Assumes that
    the picture is 'taller' than 16:9."""
    im = Image.open(filename)
    width, height = im.size
    left = 0
    top = 0
    right = width
    bottom = 9 * right / 16
    im1 = im.crop((left, top, right, bottom))
    im1.resize((1280, 720))
    im1.save("cropped_" + filename)
    #im1.show()

    return "cropped_" + filename


def make_video(img_file, audio_file):
    audio = AudioFileClip(audio_file)
    clip_len = 2#audio.duration
    clip = ImageClip(img_file).set_duration(clip_len)
    clip.resize((1280, 720))

    print("Audio/Video duration (sec): ", clip_len)
    clip = clip.set_audio(audio.set_duration(clip_len))

    clip.write_videofile(audio_file[:-4]+".mp4", fps=24) #  codec='libx264',


if __name__=='__main__':
    audio_file = "Offline & En-vy - Can You Say.m4a"
    img_file = "rocks.jpeg"
    cropped_name = crop_image_16_to_9(img_file)

    make_video(img_file=cropped_name, audio_file=audio_file)