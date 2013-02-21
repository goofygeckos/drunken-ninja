"""Goofy utility to convert between PNG and text files.

Usage:
  pngconvert.py myfile.png myfile.txt

Or:
  pngconvert.py myfile.txt myfile.png [options]
"""

import optparse
import png

def convert_png_to_txt(png_file, txt_file):
  r = png.Reader(png_file)
  f = open(txt_file, 'w')
  width, height, pixels, meta = r.read()
  print >> f, width, height
  for row in pixels:
    for index, pixel in enumerate(row, 1):
      print >> f, pixel,
      if index % width == 0:
        print >> f  # start new line

def convert_txt_to_png(txt_file, png_file, options):
  f = open(txt_file, 'r')
  width, height = map(int, f.readline().split())
  # TODO: pass any needed options to Writer
  w = png.Write(width=width, height=height)
  def row_reader():
    yield map(int, f.readline().split())
  w.write(open(png_file, 'w'), row_reader())

def option_parser():
  parser = optparse.OptionParser()
  parser.add_option('--bitdepth', dest='bitdepth',
                    help='Bit depth: from 1 to 16', default=1)
  # TODO: add any missing options here
  return parser

def main():
  parser = option_parser()
  (options, args) = parser.parse_args()

  if len(args) != 2:
    print __doc__
    parser.print_help()
  else:
    in_file, out_file = args
    if in_file.endswith('.png'):
      convert_png_to_txt(in_file, out_file)
    else:
      convert_txt_to_png(out_file, in_file, options)

if __name__ == "__main__":
  main()
