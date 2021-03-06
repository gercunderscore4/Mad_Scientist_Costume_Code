# https://stackoverflow.com/questions/20304438/how-can-i-use-the-python-imaging-library-to-create-a-bitmap
#from PIL import Image
#
#img = Image.new( 'RGB', (255,255), "black") # Create a new black image
#pixels = img.load() # Create the pixel map
#for i in range(img.size[0]):    # For every pixel:
#    for j in range(img.size[1]):
#        pixels[i,j] = (i, j, 100) # Set the colour accordingly
#
#img.show()

# https://stackoverflow.com/questions/753190/programmatically-generate-video-or-animated-gif-in-python
#import imageio
#images = []
#for filename in filenames:
#    images.append(imageio.imread(filename))
#imageio.mimsave('/path/to/movie.gif', images, duration = 1)


from PIL import Image
import imageio
from math import floor, ceil, sqrt
from random import randint
import os
import shutil

###############
# PRINT SCALE #
###############

frame_ms = 130
#flux_on = (255, 255, 255)
flux_on = (64, 36, 5)
lights = 4
loops = 4

flux_scale = [(min(255, flux_on[0] + i), min(255, flux_on[1] + i), min(255, flux_on[2] + i)) for i in range(255)]
flux_scale_mid = [(0,0,0) for i in range(int(ceil(len(flux_scale)/2)))] + flux_scale[::2]

n = len(flux_scale)
h = max(1,n//10)

img = Image.new('RGB', (n,h), "black") # create a new black image
pixels = img.load() # create the pixel map
for i in range(img.size[0]):
    for j in range(img.size[1]):
        pixels[i,j] = flux_scale[i]
img.save("brightness_scale.bmp") 
img.close()

#####################
# MAKE FLUX LED GIF #
#####################

downscale_factor = 10
flux_scale = flux_scale[::downscale_factor]
flux_scale_mid = flux_scale_mid[::downscale_factor]
n = len(flux_scale)

foldername = os.path.join(os.getcwd(),'frames')
if os.path.isdir(foldername):
    shutil.rmtree(foldername)
os.mkdir(foldername)
gif_list = []
w = (lights * 2) + 1
h = (lights * 2) + 1

frames = loops * lights

img = Image.new('RGB', (w,h), "black") # create a new black image
pixels = img.load() # create the pixel map

for f in range(frames):
    # all black
    for i in range(img.size[0]):
        for j in range(img.size[1]):
            pixels[i,j] = (0,0,0)

    # find frame in cycle
    fc = flux_scale[int(n*f/frames)]
    fl = f % lights
    pixels[fl, fl]             = fc
    pixels[w - fl - 1, fl]     = fc
    pixels[w // 2, h - fl - 1] = fc
    pixels[w // 2, h // 2]     = flux_scale_mid[int(n*f/frames)]

    # save
    filepath = os.path.join(foldername, 'frame_{:04}.gif'.format(f))
    gif_list.append(filepath)
    img.save(filepath) 
img.close()

# collect
images = []
for filepath in gif_list:
    images.append(imageio.imread(filepath))
imageio.mimsave('flux.gif', images, duration = frame_ms/1000)
shutil.rmtree(foldername)

################
# WRITE C CODE #
################

with open('flux_header.h', 'w') as fout:
    fout.write('////////////////////////////////////////////////////////////////\n')
    fout.write('// BEGIN SECTION GENERATED BY flux_capacitor.py\n')
    fout.write('\n')

    fout.write('#define FLUX_FRAME_MS {}\n'.format(frame_ms))
    fout.write('#define FLUX_LIGHTS {}\n'.format(lights))
    fout.write('#define FLUX_STEP ((now / FLUX_FRAME_MS) % FLUX_LIGHTS)\n')
    fout.write('#define FLUX_ON_COUNT {}\n'.format(n))
    fout.write('const rgb_color flux_off =  {  0,   0,   0};\n')
    fout.write('const rgb_color flux_on[] = {')
    for i in range(n):
        fout.write('{{{},{},{}}}'.format(flux_scale[i][0], flux_scale[i][1], flux_scale[i][2]))
        if i < (n-1):
            fout.write(',')
    fout.write('};\n')
    #for i in range(n):
    #    fout.write('{{{:3}, {:3}, {:3}}}'.format(flux_scale[i][0], flux_scale[i][1], flux_scale[i][2]))
    #    if i < (n-1):
    #        fout.write(',\n                             ')
    #fout.write('};\n')
    fout.write('const rgb_color flux_on_mid[] = {')
    for i in range(n):
        fout.write('{{{},{},{}}}'.format(flux_scale_mid[i][0], flux_scale_mid[i][1], flux_scale_mid[i][2]))
        if i < (n-1):
            fout.write(',')
    fout.write('};\n')
    #for i in range(n):
    #    fout.write('{{{:3}, {:3}, {:3}}}'.format(flux_scale_mid[i][0], flux_scale_mid[i][1], flux_scale_mid[i][2]))
    #    if i < (n-1):
    #        fout.write(',\n                                 ')
    #fout.write('};\n')
    fout.write('\n')

    fout.write('#define FLUX_POWER_UP_LOOPS {}\n'.format(loops))
    fout.write('\n')
    fout.write('inline unsigned int flux_time (void) {\n')
    fout.write('    return min(FLUX_ON_COUNT - 1, ((now - switch_start) * FLUX_ON_COUNT) / (FLUX_FRAME_MS * FLUX_POWER_UP_LOOPS));\n')
    fout.write('}\n')
    fout.write('\n')
    
    fout.write('// END SECTION GENERATED BY flux_capacitor.py\n')
    fout.write('////////////////////////////////////////////////////////////////\n')

