""" Implementation of Neural Style Transfer turorial from:
    https://www.tensorflow.org/tutorials/generative/style_transfer

    HOW TO USE IT
    - If you have a relatively new NVIDIA GPU (for me GT 750M works fine)
      with driver version 418.96+, I recommend installing CUDA 10.1.
      https://developer.nvidia.com/cuda-10.1-download-archive-base
    - I also recommend using conda environments:
      https://docs.conda.io/projects/conda/en/latest/user-guide/install/
    - make an environment for tensorflow and install the necessary libraries
      using the conda cheat sheet:
      https://docs.conda.io/projects/conda/en/4.6.0/_downloads/52a95608c49671267e40c689e0bc00ca/conda-cheatsheet.pdf
    - change globals max_dim, content_path and style_path the way you want to with your pictures
    - running the script like this will save a jpg every 50 training steps,
      which can then be made into a GIF with make_GIF.py
"""
import tensorflow as tf
import numpy as np
import PIL.Image
import time
import matplotlib.pyplot as plt
import IPython.display as display

# images will be loaded with this maximum length
# big images may cause GPU memory issues
max_dim = 64

content_path = "YellowLabradorLooking.jpg"
style_path = "VassilyKandinsky1913Composition7.jpg"


def imshow(image, title=None):
    if len(image.shape) > 3:
        image = tf.squeeze(image, axis=0)

    plt.imshow(image)
    if title:
        plt.title(title)
    plt.show()


def tensor_to_image(tensor):
    tensor = tensor*255
    tensor = np.array(tensor, dtype=np.uint8)
    if np.ndim(tensor)>3:
        assert tensor.shape[0] == 1
        tensor = tensor[0]
    return PIL.Image.fromarray(tensor)


def load_img(path_to_img):
    img = tf.io.read_file(path_to_img)
    img = tf.image.decode_image(img, channels=3)
    img = tf.image.convert_image_dtype(img, tf.float32)

    shape = tf.cast(tf.shape(img)[:-1], tf.float32)
    long_dim = max(shape)
    scale = max_dim / long_dim

    new_shape = tf.cast(shape * scale, tf.int32)

    img = tf.image.resize(img, new_shape)
    img = img[tf.newaxis, :]
    return img


def vgg_layers(layer_names):
    """ Creates a vgg model that returns a list of intermediate output values."""
    # Load our model. Load pretrained VGG, trained on imagenet data
    vgg = tf.keras.applications.VGG19(include_top=False, weights='imagenet')
    vgg.trainable = False

    outputs = [vgg.get_layer(name).output for name in layer_names]

    model = tf.keras.Model([vgg.input], outputs)
    return model

# gram matrix to derive the style through means and correlations across the different feature maps
def gram_matrix(input_tensor):
    result = tf.linalg.einsum('bijc,bijd->bcd', input_tensor, input_tensor)
    input_shape = tf.shape(input_tensor)
    num_locations = tf.cast(input_shape[1]*input_shape[2], tf.float32)
    return result / num_locations


class StyleContentModel(tf.keras.models.Model):
    def __init__(self, style_layers, content_layers):
        super(StyleContentModel, self).__init__()
        self.vgg = vgg_layers(style_layers + content_layers)
        self.style_layers = style_layers
        self.content_layers = content_layers
        self.num_style_layers = len(style_layers)
        self.vgg.trainable = False

    def call(self, inputs):
        """Expects float input in [0,1]"""
        inputs = inputs * 255.0
        preprocessed_input = tf.keras.applications.vgg19.preprocess_input(inputs)
        outputs = self.vgg(preprocessed_input)
        style_outputs, content_outputs = (outputs[:self.num_style_layers],
                                          outputs[self.num_style_layers:])

        style_outputs = [gram_matrix(style_output)
                         for style_output in style_outputs]

        content_dict = {content_name: value
                        for content_name, value
                        in zip(self.content_layers, content_outputs)}

        style_dict = {style_name: value
                      for style_name, value
                      in zip(self.style_layers, style_outputs)}

        return {'content': content_dict, 'style': style_dict}


def clip_0_1(image):
  return tf.clip_by_value(image, clip_value_min=0.0, clip_value_max=1.0)


def style_content_loss(outputs):
    style_outputs = outputs['style']
    content_outputs = outputs['content']
    style_loss = tf.add_n([tf.reduce_mean((style_outputs[name]-style_targets[name])**2)
                           for name in style_outputs.keys()])
    style_loss *= style_weight / num_style_layers

    content_loss = tf.add_n([tf.reduce_mean((content_outputs[name]-content_targets[name])**2)
                             for name in content_outputs.keys()])
    content_loss *= content_weight / num_content_layers
    loss = style_loss + content_loss
    return loss


@tf.function()
def train_step(image):
    with tf.GradientTape() as tape:
        outputs = extractor(image)
        loss = style_content_loss(outputs)
        # this line is added to
        loss += total_variation_weight * tf.image.total_variation(image)

    grad = tape.gradient(loss, image)
    opt.apply_gradients([(grad, image)])
    image.assign(clip_0_1(image))


def train(image, epochs=1, steps_per_epoch = 1):
    start = time.time()
    step = 0
    for n in range(epochs):
        new_start = time.time()
        for m in range(steps_per_epoch):
            step += 1
            train_step(image)
            print(".", end='')
            # save intermediate results
            if step%50==0:
                out = tensor_to_image(image)
                out.save("image_step_{}.jpg".format(step))

        # save+show current image every epoch
        #out = tensor_to_image(image)
        #out.save("image_step_{}.jpg".format(step))
        #display.clear_output(wait=True)
        #display.display(tensor_to_image(image))
        print("Train step: {}".format(step))
        print("time: {}".format(time.time()-new_start))

    end = time.time()
    print("Total time: {:.1f}".format(end - start))


if __name__=="__main__":

    print("loading images")
    content_image = load_img(content_path)
    style_image = load_img(style_path)

    # pre-trained image classification network VGG19:
    print("loading VGG19")
    vgg = tf.keras.applications.VGG19(include_top=False, weights='imagenet')

    # we will access the activations of that network to
    # extract its content and style understanding
    # Content layer where will pull our feature maps
    content_layers = ['block5_conv2']

    # Style layer of interest
    style_layers = ['block1_conv1',
                    'block2_conv1',
                    'block3_conv1',
                    'block4_conv1',
                    'block5_conv1']

    num_content_layers = len(content_layers)
    num_style_layers = len(style_layers)

    style_extractor = vgg_layers(style_layers)
    print("getting outputs")
    style_outputs = style_extractor(style_image * 255)

    extractor = StyleContentModel(style_layers, content_layers)

    results = extractor(tf.constant(content_image))

    style_results = results['style']

    style_targets = extractor(style_image)['style']
    content_targets = extractor(content_image)['content']

    image = tf.Variable(content_image)

    opt = tf.optimizers.Adam(learning_rate=0.02, beta_1=0.99, epsilon=1e-1)

    style_weight = 1e-2
    content_weight = 1e4
    total_variation_weight = 30

    train(image, epochs=10, steps_per_epoch=100)





