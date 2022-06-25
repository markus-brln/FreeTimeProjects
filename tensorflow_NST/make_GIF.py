import glob
import imageio

anim_file = 'newgif.gif'
image_names = 'image*.jpg'


def make_gif():
    with imageio.get_writer(anim_file, mode='I') as writer:
        filenames = glob.glob(image_names)
        filenames = sorted(filenames)
        print("files that will be used: ")
        for filename in filenames:
            print(filename)
        last = -1
        for i, filename in enumerate(filenames):
            frame = 2 * (i ** 0.5)
            if round(frame) > round(last):
                last = frame
            else:
                continue
            image = imageio.imread(filename)
            for j in range(2):
                writer.append_data(image)
        image = imageio.imread(filename)
        for j in range(2):
            writer.append_data(image)


if __name__ == "__main__":
    make_gif()
